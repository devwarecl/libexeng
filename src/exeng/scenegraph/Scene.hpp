
#ifndef __EXENG_SCENEGRAPH_SCENE_HPP__
#define __EXENG_SCENEGRAPH_SCENE_HPP__

#include "../Object.hpp"
#include "../math/TVector.hpp"
#include "../graphics/Color.hpp"

#include <vector>

namespace exeng {
    namespace scenegraph {
        class EXENGAPI Light;
        class EXENGAPI Camera;
        class EXENGAPI SceneNode;
        class EXENGAPI Material;
		class EXENGAPI Geometry;

        /**
         *@brief Clase de grafos de escena
         */
        class EXENGAPI Scene : public Object {
        public:
            Scene();
            
            virtual ~Scene();
            
            /**
             * @brief Devuelve el nodo raiz de la escena
             */
            auto getRootNodePtr() -> SceneNode*;
            
            
            /**
             * @brief Agrega la camera indicada al grafo de escena
             */
            auto addCamera(Camera *camera) -> SceneNode*;
            
            
            /**
             * @brief Agrega la luz indicada al grafo de escena
             */
            auto addLight(Light *light) -> SceneNode*;
            
            
            /**
             * @brief Establece el color de fondo de la escena
             * @param color Un color como vector de cuatro componentes en punto flotante, 
             * representado como RGBA
             */
            auto setBackgroundColor(const exeng::graphics::Color &color) -> void;
            
            
            /**
             * @brief Devuelve el color de fondo de la escena
             * @return Color RGBA, punto flotante, encapsulado en un objeto exeng::graphics::Color
             */
            auto getBackgroundColor() const -> exeng::graphics::Color;


        private:
            struct Private;
            Private* impl;
        };
    }
}

#endif // SCENE_HPP
