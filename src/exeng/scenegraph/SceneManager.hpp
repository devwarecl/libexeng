/**
 * @file SceneManager.hpp
 * @brief Defines the SceneManager class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_SCENEMANAGER_HPP__
#define __EXENG_SCENEGRAPH_SCENEMANAGER_HPP__

#include <exeng/Config.hpp>
#include <exeng/Root.hpp>
#include <exeng/graphics/Material.hpp>

#include <exeng/scenegraph/SceneRenderer.hpp>
#include <exeng/scenegraph/Scene.hpp>
#include <exeng/scenegraph/Camera.hpp>

namespace exeng { namespace scenegraph {
    /**
     * @brief Scene Manager. Handles the rendering of the scene.
     */
    class EXENGAPI SceneManager {
        friend class exeng::Root;

    private:
        SceneManager(Root* root);
    
    public:
        /**
         * @brief Get the parent root object.
         */
        const Root* getRoot() const;
        
        /**
         * @brief Get the parent root object.
         */
        Root* getRoot();
        
        /**
         * @brief Set the current scene renderer.
         */
        void setSceneRenderer(SceneRenderer *renderer);
        
        /**
         * @brief Get the currently scene renderer.
         */
        SceneRenderer* getSceneRenderer();
        
        /**
         * @brief Get the currently used scene renderer.
         */
        const SceneRenderer* getSceneRenderer() const;
        
        /**
         * @brief Set the scene to render.
         */
        void setScene(Scene *scene);
        
        /**
         * @brief Get the current scene.
         */
        Scene* getScene();
        
        /**
         * @brief Get the current scene.
         */
        const Scene* getScene() const;
        
        /**
         * @brief Renders the scene using the currently setted renderer.
         */
        void render(const Camera *camera);
        
    private:
        struct Private;
        Private *impl = nullptr;
    }; 
}}

#endif // __EXENG_SCENEGRAPH_SCENEMANAGER_HPP__
