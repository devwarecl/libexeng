/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <cassert>
#include <vector>
#include <stdexcept>
#include <boost/checked_delete.hpp>

#include <exeng/scenegraph/SceneNode.hpp>

using namespace exeng;
using namespace exeng::scenegraph;

namespace exeng { namespace scenegraph {

    //! SceneNode private data
    struct SceneNode::Private {
        std::string name;       //! Node name
        Matrix4f transform;     //! Node transformation
        SceneNode* parentPtr;   //! 
        SceneNodes childs;      //! Node childs
        SceneNodeData *data;    //! Private data
        
        Private() {   
            this->data = nullptr;
            this->parentPtr = nullptr;
            this->transform = identity<float, 4>();
        }
                
        ~Private() {}
        
        SceneNodesIterator getChild(const std::string &name) {
            auto &childs = this->childs;
            
            return std::find_if(std::begin(childs), std::end(childs), [&name](SceneNode *node) {
                return node->impl->name == name;
            });
        }
    };
}}

namespace exeng { namespace scenegraph {
        
    SceneNode::SceneNode() {
        this->impl = new SceneNode::Private();
    }


    SceneNode::SceneNode(const std::string &name) {
        this->impl = new SceneNode::Private();

        // Pueden existir nodos hermanos que tengan, potencialmente, 
        // el mismo nombre, asi que es preferible llamar al metodo.
        this->setName(name);
    }
    
    
    SceneNode::SceneNode(const std::string &name, SceneNode *parent) {
        this->impl = new SceneNode::Private();
        this->setName(name);
        this->setParent(parent);
    }
    
    
    SceneNode::~SceneNode() {
        if (this->impl == nullptr) {
            return;
        }
        
        // delete childs also
        for (SceneNode *child : this->impl->childs) {
            if (child == nullptr) {
                continue;
            }
            
            delete child;
        }
        
        boost::checked_delete(this->impl);
    }
    
    
    std::string SceneNode::toString() const {
        assert(this->impl != nullptr);

        if (this->hasParent() == false) {
            return "";
        } else {
            return this->getParent()->toString() + "\\" + this->getName();
        }
    }


    Matrix4f SceneNode::getTransform() const {
        assert(this->impl != nullptr);
        return this->impl->transform;
    }


    void SceneNode::setTransform(const Matrix4f& transform) {
        assert(this->impl != nullptr);
        this->impl->transform = transform;
    }


    std::string SceneNode::getName() const {
        assert(this->impl != nullptr);

        // Devuelve el nombre por valor 
        return this->impl->name;
    }


    void SceneNode::setName(const std::string &name) {
        assert(this->impl != nullptr);

        if (this->hasParent() == true) {
            if (this->getParent()->existChild(name) == true) {
                throw std::logic_error("Ya existe un nodo hermano con ese nombre.");
            }
        }
                
        this->impl->name = name;
    }


    int SceneNode::getChildCount() const {
        assert(this->impl != nullptr);
        return static_cast<int>(this->impl->childs.size());
    }


    SceneNode* SceneNode::getChild(int index) const {
        assert(this->impl != nullptr);
        return this->impl->childs[index];
    }


    SceneNode* SceneNode::getChild(const std::string& name) {
        assert(this->impl != nullptr);

        SceneNode *childPtr = nullptr;

        childPtr = *this->impl->getChild(name);

        // Como no existe el nodo hijo, instanciamos uno y devolvemos su referencia
        if (childPtr == nullptr) {
            childPtr = this->addChild(name);
        }

        return childPtr;
    }


    SceneNode* SceneNode::getChild(const std::string& name) const {
        assert(this->impl != nullptr);

        SceneNode *childPtr = nullptr;
                
        childPtr = *this->impl->getChild(name);

        if (childPtr == nullptr) {
            // Lanzar una excpecion, ya que no podemos modificar al grafo de escena 
            // si este es constante
            std::string msg;

            msg += "El nodo con el nombre '";
            msg += name;
            msg += "' no fue encontrado.";

            throw std::logic_error(msg);
        }

        return childPtr;
    }


    SceneNode* SceneNode::getParent() const {
        assert(this->impl != nullptr);

        if (this->hasParent() == false) {
            std::string msg;

            msg += "El nodo " + this->toString();
            msg += " no posee nodo padre.";

            throw std::logic_error(msg);
        }

        return this->impl->parentPtr;
    }


    void SceneNode::setParent(SceneNode* parent) {
        assert(this->impl != nullptr);

        // Para cambiar el padre, es necesario primero desvincular al nodo 
        // de su padre previo (si lo tiene)
        if (this->hasParent() == true) {
            this->getParent()->removeChild(this);
        }

        // Ahora, agregamos el nuevo nodo al padre
        parent->addChild(this);
    }


    bool SceneNode::hasParent() const {
        assert(this->impl != nullptr);
        return this->impl->parentPtr != nullptr;
    }


    bool SceneNode::existChild(const std::string &name) const {
        assert(this->impl != nullptr);

        // Si el nodo hijo con el nombre indicado existe, entonces devolvemos true
        return *this->impl->getChild(name) != nullptr;
    }


    SceneNode* SceneNode::addChild(SceneNode *childPtr) {
        assert(this->impl != nullptr);

        // Debemos considerar que este metodo debe modificar los padres directamente, 
        // ya que en la implementacion actual, otros metodos relacionados con la modificacion
        // de la jerarquia del grafo de escena son depedientes de este.
        if (childPtr->hasParent() == true) {
            // Desvincular al nodo padre 
            childPtr->getParent()->removeChild(childPtr);
        }
                
        childPtr->impl->parentPtr = this;
        this->impl->childs.push_back(childPtr);

        return childPtr;
    }


    SceneNode* SceneNode::removeChild(const std::string& name) {
        assert(this->impl != nullptr);

        // Implementacion rapida y sucia
        SceneNodesIterator it = this->impl->getChild(name);
        SceneNode* child = *it;

        return this->removeChild(child);
    }


    SceneNode* SceneNode::removeChild(SceneNode* childPtr) {
        assert(this->impl != nullptr);

        // Determinar si el padre de este nodo somos nosotros antes de continuar
        if (this->impl->parentPtr == this) {
            // Buscar el iterador correspondiente
            auto &childs = this->impl->childs;
            auto it = childs.begin();
            
            for (it=childs.begin(); it!=childs.end(); ++it) {
                if (*it == childPtr) {
                    break;
                }
            }

            // Indica en tiempo de ejecucion errores internos
            assert(it != childs.end());
                    
            // Sacar el nodo de la lista de los hijos
            this->impl->childs.erase(it);
            childPtr->impl->parentPtr = nullptr;

            return childPtr;
        } else {
            std::string msg;

            msg += "SceneNode::removeChildPtr: The node '" + 
            msg += childPtr->getName();
            msg += "' doesn't belong to this hierarchy. ";
            msg += this->toString();

            throw std::logic_error(msg);
        }	
    }


    SceneNode* SceneNode::addChild(const std::string& name) {
        assert(this->impl != nullptr);

        SceneNode* childPtr = new SceneNode(name);
        return this->addChild(childPtr);
    }


    void SceneNode::orphan() {
        assert(this->impl != nullptr);
        
        if (this->hasParent() == true) {
            this->getParent()->removeChild(this);
        }
    }

            
    void SceneNode::setData(SceneNodeData* data) {
        assert(this->impl != nullptr);
        
        this->impl->data = data;
    }


    SceneNodeData* SceneNode::getData() const {
        assert(this->impl != nullptr);
        
        return this->impl->data;
    }
    
    
    const SceneNodes& SceneNode::getChilds() const {
        assert(this->impl != nullptr);
        
        return this->impl->childs;
    }
}}
