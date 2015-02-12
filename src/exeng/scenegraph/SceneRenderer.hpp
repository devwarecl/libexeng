/**
 * @file ISceneRenderer.hpp
 * @brief Definition of the ISceneRenderer interface.
 */


/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_SCENERENDERER_HPP__
#define __EXENG_SCENEGRAPH_SCENERENDERER_HPP__

#include <exeng/Config.hpp>

namespace exeng { namespace scenegraph {
    
    class EXENGAPI Scene;
    class EXENGAPI Camera;
    
    /**
     * @brief Interface to a scene renderer
     */
	class EXENGAPI SceneRenderer {
    public:
        virtual ~SceneRenderer();
        
        /**
         * @brief Get the current scene.
         */
        virtual const Scene* getScene() const = 0;
        
        /**
         * @brief Set the current scene.
         * @param scene The scene to render. Cannot be a nullptr.
         * @throw std::invalid_argument When the scene is a nullptr (On debug builds).
         */
        virtual void setScene(const Scene *scene) = 0;
        
        /**
         * @brief Render the current scene using the camera
         * @param camera The current scene to render.
         * @throw std::invalid_argument When the supplied camera doesn't belong to the current scene.
         */
        virtual void renderScene(const Camera *camera) = 0;
    };
    
    inline SceneRenderer::~SceneRenderer() {}
}}

#endif // __EXENG_SCENEGRAPH_SCENERENDERER_HPP__
