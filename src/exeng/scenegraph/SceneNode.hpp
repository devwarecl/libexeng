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


#ifndef __EXENG_SCENE_SCENENODE_HPP__
#define __EXENG_SCENE_SCENENODE_HPP__

#include <vector>

#include <exeng/Object.hpp>
#include <exeng/math/TMatrix.hpp>

namespace exeng {
	namespace scenegraph {
        class EXENGAPI SceneNode;
        class EXENGAPI SceneNodeData;
        
        typedef std::vector<SceneNode*> SceneNodeVector;
        typedef SceneNodeVector::iterator SceneNodeVectorIt;
        
        /**
         * @brief Nodo de un grafo de escena. Representa a cualquier entidad existente en un 
         * grafo de escena, y que puede ser representada en cualquier tipo de medio. 
         */
        class EXENGAPI SceneNode : public Object {
        public:
            SceneNode();
            explicit SceneNode(const std::string& name);

            /**
             * @brief Libera la memoria utilizada por el nodo y por sus nodos hijos
             */
            virtual ~SceneNode();

            /**
             * @brief Devuelve una representacion como cadena de texto del nodo de escena.
             * @return 
             */
            virtual std::string toString() const;
            
            /**
             * @brief Devuelve la transformacion local que condiciona al nodo de escena y a sus hijos
             * @return 
             */
            exeng::math::Matrix4f getTransform() const;
            
            /**
             * @brief Establece la transformacion actual que modifica al nodo, y a todos y cada uno de sus nodos hijos
             * @param transform
             */
            void setTransform(const exeng::math::Matrix4f& transform);
            
            /**
             * @brief Devuelve el nombre del nodo. 
             * @return 
             */
            std::string getName() const;
            
            /**
             * @brief Establece el nombre del nodo, como una cadena de texto. Esta cadena de texto solo puede 
             * poseer subrayados, letras y numeros. Otros tipos de caracteres no estan permitidos. No debe existir 
             * ningun nodo hermano que tenga el mismo nombre. De ser asi, se lanza una excepcion std::logic_error
             * @param name
             */
            void setName(const std::string &name);
            
            /**
             * @brief Devuelve la cantidad total de nodos hijos existentes en el nodo
             * @return 
             */
            int getChildCount() const;
            
            /**
             * @brief Devuelve el nodo hijo que se encuentra en la posicion indicada
             * @param index
             */
            SceneNode* getChildPtr(int index) const;
            
            /**
             * @brief Devuelve el nodo hijo que tenga el nombre indicado, pero lanza una excepcion si 
             * no es encontrado.
             * @param name
             */
            SceneNode* getChildPtr(const std::string& name) const;
            
            /**
             * @brief Devuelve el nodo hijo que tenga el nombre indicado. En caso de que no exista el nodo con el 
             * nombre indicado, se crea un nuevo.
             * @param name Una cadena de texto, con el nombre del nodo hijo a obtener.
             */
            SceneNode* getChildPtr(const std::string& name);
            
            /**
             * @brief Comprueba si el nodo hijo indicado existe. 
             * @param name
             * @return 
             */
            bool existChild(const std::string& name) const;
            
            /**
             * @brief Devuelve true si el nodo posee un nodo padre, y false en caso contrario
             * @return 
             */
            bool hasParent() const;

            /**
             * @brief Devuelve el nodo padre de este nodo
             */
            SceneNode* getParentPtr() const;
            
            /**
             * @brief Establece el nodo padre de este nodo
             * @param parent
             */
            void setParentPtr(SceneNode* parent);

            /**
             * @brief Busca el nodo que tenga el nombre indicado.
             * @param name
             */
            SceneNode* findNodePtr(const std::string &name) const;
            
            /**
             * @brief Agrega un nuevo nodo hijo al grafo de escena.El grafo de escena se hace responsable
             * por el tiempo de vida del nodo 
             * @param childPtr
             */
            SceneNode* addChildPtr(SceneNode *childPtr);
            
            /**
             * @brief Saca el nodo hijo indicado del nodo de escena. Si no existe el nodo indicado, se lanza 
             * una excepcion de tipo std::logic_error. Devuelve un puntero al nodo hijo, para que el cliente se 
             * haga responsable de la vida del objeto.
             * @param name
             */
            SceneNode* removeChildPtr(const std::string& name);

            /**
             * @brief Saca el nodo hijo. 
             * @param childRef
             */
            SceneNode* removeChildPtr(SceneNode* childRef);

            /**
             * @brief Agrega un nuevo nodo hijo al nodo de escena. Si existe otro nodo hijo con el mismo nombre, se 
             * lanza una excepcion std::logic_error
             * @param name
             */
            SceneNode* addChildPtr(const std::string& name);

            /**
             * @brief Hace que este nodo se quede sin padre
             */
            void orphan();
            
            /**
             * @brief Establece la informacion asociada al nodo de escena actual 
             * @param data
             */
            void setDataPtr(SceneNodeData* data);

            /**
             * @brief Devuelve la informacion asociada al nodo de escena actual
             */
            SceneNodeData* getDataPtr() const;
            
            /**
             * @brief Devuelve una referencia a la lista de nodos hijos actual del nodo de escena.
             */
            const SceneNodeVector& getChilds() const;
            
        private:
            struct Private;
            Private *impl;
        };
    }
}

#endif
