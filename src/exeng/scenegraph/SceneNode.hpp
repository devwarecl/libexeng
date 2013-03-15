/**
 * @brief Documentacion pendiente
 */


#ifndef __EXENG_SCENE_SCENENODE_HPP__
#define __EXENG_SCENE_SCENENODE_HPP__

#include <vector>

#include "../Object.hpp"
#include "../math/TMatrix.hpp"

namespace exeng
{
	namespace scenegraph
    {
        class EXENGAPI SceneNode;
        class EXENGAPI SceneNodeData;
        
        typedef std::vector<SceneNode*> SceneNodeVector;
        typedef SceneNodeVector::iterator SceneNodeVectorIterator;
        
        
        /**
         * @brief Nodo de un grafo de escena. Representa a cualquier entidad existente en un 
         * grafo de escena, y que puede ser representada en cualquier tipo de medio. 
         */
        class EXENGAPI SceneNode : public Object
        {
        public:
            /**
             * @brief Documentacion pendiente
             */

            SceneNode();

            /**
             * @brief Documentacion pendiente
             */

            explicit SceneNode(const std::string& name);

            /**
             * @brief Libera la memoria utilizada por el nodo y por sus nodos hijos
             */
            virtual ~SceneNode();

            /**
             * @brief Devuelve una representacion como cadena de texto del nodo de escena.
             * @return 
             */
            virtual auto toString() const -> std::string;
            
            
            /**
             * @brief Devuelve la transformacion local que condiciona al nodo de escena y a sus hijos
             * @return 
             */
            auto getTransform() const -> exeng::math::Matrix4f;
            
            
            /**
             * @brief Establece la transformacion actual que modifica al nodo, y a todos y cada uno de sus nodos hijos
             * @param transform
             */
            auto setTransform(const exeng::math::Matrix4f& transform) -> void;

            
            /**
             * @brief Devuelve el nombre del nodo. 
             * @return 
             */
            auto getName() const -> std::string;

            
            /**
             * @brief Establece el nombre del nodo, como una cadena de texto. Esta cadena de texto solo puede 
             * poseer subrayados, letras y numeros. Otros tipos de caracteres no estan permitidos. No debe existir 
             * ningun nodo hermano que tenga el mismo nombre. De ser asi, se lanza una excepcion std::logic_error
             * @param name
             */
            auto setName(const std::string &name) -> void;
            
            
            /**
             * @brief Devuelve la cantidad total de nodos hijos existentes en el nodo
             * @return 
             */
            auto getChildCount() const ->  int;

            
            /**
             * @brief Devuelve el nodo hijo que se encuentra en la posicion indicada
             * @param index
             */
            auto getChildPtr(int index) const -> SceneNode*;
            
            
            /**
             * @brief Devuelve el nodo hijo que tenga el nombre indicado, pero lanza una excepcion si 
             * no es encontrado.
             * @param name
             */
            auto getChildPtr(const std::string& name) const -> SceneNode*;
            
            
            /**
             * @brief Devuelve el nodo hijo que tenga el nombre indicado. En caso de que no exista el nodo con el 
             * nombre indicado, se crea un nuevo.
             * @param name Una cadena de texto, con el nombre del nodo hijo a obtener.
             */
            auto getChildPtr(const std::string& name) -> SceneNode*;
            
            
            /**
             * @brief Comprueba si el nodo hijo indicado existe. 
             * @param name
             * @return 
             */
            auto existChild(const std::string& name) const -> bool;
            
            
            /**
             * @brief Devuelve true si el nodo posee un nodo padre, y false en caso contrario
             * @return 
             */
            auto hasParent() const -> bool;

            
            /**
             * @brief Devuelve el nodo padre de este nodo
             */
            auto getParentPtr() const -> SceneNode*;

            
            /**
             * @brief Establece el nodo padre de este nodo
             * @param parent
             */
            auto setParentPtr(SceneNode* parent) -> void;

            
            /**
             * @brief Busca el nodo que tenga el nombre indicado.
             * @param name
             */
            auto findNodePtr(const std::string &name) const -> SceneNode*;
            
            
            /**
             * @brief Agrega un nuevo nodo hijo al grafo de escena.El grafo de escena se hace responsable
             * por el tiempo de vida del nodo 
             * @param childPtr
             */
            auto addChildPtr(SceneNode *childPtr) -> SceneNode*;
            
            
            /**
             * @brief Saca el nodo hijo indicado del nodo de escena. Si no existe el nodo indicado, se lanza 
             * una excepcion de tipo std::logic_error. Devuelve un puntero al nodo hijo, para que el cliente se 
             * haga responsable de la vida del objeto.
             * @param name
             */
            auto removeChildPtr(const std::string& name) -> SceneNode*;

            
            /**
             * @brief Saca el nodo hijo. 
             * @param childRef
             */
            auto removeChildPtr(SceneNode* childRef) -> SceneNode*;

            
            /**
             * @brief Agrega un nuevo nodo hijo al nodo de escena. Si existe otro nodo hijo con el mismo nombre, se 
             * lanza una excepcion std::logic_error
             * @param name
             */
            auto addChildPtr(const std::string& name) -> SceneNode*;

            
            /**
             * @brief Hace que este nodo se quede sin padre
             */
            auto orphan() -> void;
            
            
            /**
             * @brief Establece la informacion asociada al nodo de escena actual 
             * @param data
             */
            auto setDataPtr(SceneNodeData* data) -> void ;

            
            /**
             * @brief Devuelve la informacion asociada al nodo de escena actual
             */
            auto getDataPtr() const -> SceneNodeData*;
            
            
            /**
             * @brief Devuelve una referencia a la lista de nodos hijos actual del nodo de escena.
             */
            auto getChilds() const -> const SceneNodeVector&;
            
            
        private:
            struct Private;
            Private *impl;
        };
    }
}

#endif
