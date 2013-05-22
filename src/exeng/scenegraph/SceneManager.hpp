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

namespace exeng {
    namespace scenegraph {
        
        class EXENGAPI Root;
        class EXENGAPI Scene;
        class EXENGAPI ISceneRenderer;
        
        /**
         * @brief Scene Manager. Handles the rendering of the scene.
         */
        class EXENGAPI SceneManager {
        public:
            explicit SceneManager(Root *root);
            
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
            void setSceneRenderer(ISceneRenderer *renderer);
            
            /**
             * @brief Get the current scene renderer.
             */
            ISceneRenderer* getSceneRenderer();
            
            /**
             * @brief Get the current used scene renderer.
             */
            const ISceneRenderer* getSceneRenderer() const;
            
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
             * @brief Renders the scene using the currently 
             * setted renderer.
             */
            void render();
            
        private:
            struct Private;
            Private *impl;
        }; 
    }
}

#endif // SCENEMANAGER_HPP
