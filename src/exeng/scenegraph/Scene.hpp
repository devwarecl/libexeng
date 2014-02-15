/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_SCENE_HPP__
#define __EXENG_SCENEGRAPH_SCENE_HPP__

#include <vector>
#include <exeng/Object.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/graphics/Color.hpp>

namespace exeng { namespace graphics {
    class EXENGAPI Material;
}}

namespace exeng { namespace scenegraph {
    
    class EXENGAPI Light;
    class EXENGAPI Camera;
    class EXENGAPI SceneNode;
    class EXENGAPI Geometry;
    
    /**
     *  @brief Clase de grafos de escena
     */
    class EXENGAPI Scene : public Object {
    public:
        Scene();
        virtual ~Scene();
        
        /**
         * @brief Devuelven el nodo raiz de la escena
         */
        SceneNode* getRootNode();
        const SceneNode *getRootNode() const;
        
        /**
         * @brief Agrega la camera indicada al grafo de escena
         */
        SceneNode* addCamera(Camera *camera);
        SceneNode* addCamera();
        
        
        /**
         * @brief Agrega la luz indicada al grafo de escena
         */
        SceneNode* addLight(Light *light);
        
        /**
         * @brief Establece el color de fondo de la escena
         * @param color Un color como vector de cuatro componentes en punto flotante, 
         * representado como RGBA
         */
        void setBackgroundColor(const exeng::graphics::Color &color);
        
        /**
         * @brief Devuelve el color de fondo de la escena
         * @return Color RGBA, punto flotante, encapsulado en un objeto exeng::graphics::Color
         */
        exeng::graphics::Color getBackgroundColor() const;

    private:
        struct Private;
        Private* impl;
    };
}}

#endif
