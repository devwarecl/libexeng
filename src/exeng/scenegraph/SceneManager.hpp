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

#include <memory>
#include <exeng/Config.hpp>
#include <exeng/Root.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/scenegraph/SceneRenderer.hpp>
#include <exeng/scenegraph/SceneNodeAnimator.hpp>
#include <exeng/scenegraph/Scene.hpp>
#include <exeng/scenegraph/Camera.hpp>

namespace exeng { namespace scenegraph {

    /**
     * @brief Scene Manager. Handles the rendering and dynamic updating of the scene.
     */
    class EXENGAPI SceneManager {
    public:
		SceneManager(std::unique_ptr<Scene> scene);

        /**
         * @brief Set the current scene renderer.
		 * 
		 * Destroy the previously setted renderer.
         */
        void setSceneRenderer(std::unique_ptr<SceneRenderer> renderer);
        
        /**
         * @brief Get the currently scene renderer.
         */
        SceneRenderer* getSceneRenderer();
        
        /**
         * @brief Get the currently used scene renderer.
         */
        const SceneRenderer* getSceneRenderer() const;
        
        /**
         * @brief Get the current scene.
         */
        Scene* getScene();
        
        /**
         * @brief Get the current scene.
         */
        const Scene* getScene() const;
        
		void addAnimator(SceneNodeAnimator *animator);

		void removeAnimator(SceneNodeAnimator *animator);

		/**
		 * @brief Update all animators.
		 */
		void update(double seconds);

        /**
         * @brief Renders the current scene using the current renderer.
         */
        void render(const Camera *camera);
        
    private:
        struct Private;
        Private *impl = nullptr;
    }; 
}}

#endif // __EXENG_SCENEGRAPH_SCENEMANAGER_HPP__
