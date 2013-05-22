/**
 * @file SceneManager.hpp
 * @brief Implementation of the class SceneManager class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <cassert>
#include <stdexcept>
#include <string>
#include <exeng/scenegraph/SceneManager.hpp>
#include <exeng/scenegraph/ISceneRenderer.hpp>

namespace exeng {
    namespace scenegraph {
        
        struct SceneManager::Private {
            Root *root;
            ISceneRenderer *renderer;
            Scene *scene;
            
            Private() : root(nullptr), renderer(nullptr), scene(nullptr) {}
        };
        
        
        SceneManager::SceneManager(Root *root) : impl(nullptr) {
            this->impl = new SceneManager::Private();
            this->impl->root = root;
        }
        
        
        const Root* SceneManager::getRoot() const {
            assert(this->impl != nullptr);
            return this->impl->root;
        }
        
        
        Root* SceneManager::getRoot() {
            assert(this->impl != nullptr);
            return this->impl->root;
        }
        
        
        void SceneManager::setSceneRenderer(ISceneRenderer *renderer) {
            assert(this->impl != nullptr);
            this->impl->renderer = renderer;
        }
        
        
        ISceneRenderer* SceneManager::getSceneRenderer() {
            assert(this->impl != nullptr);
            return this->impl->renderer;
        }
        
        
        const ISceneRenderer* SceneManager::getSceneRenderer() const {
            assert(this->impl != nullptr);
            return this->impl->renderer;
        }
        
        
        void SceneManager::setScene(Scene *scene) {
            assert(this->impl != nullptr);
            this->impl->scene = scene;
        }
        
        
        Scene* SceneManager::getScene() {
            assert(this->impl != nullptr);
            return this->impl->scene;
        }
        
        
        const Scene* SceneManager::getScene() const {
            assert(this->impl != nullptr);
            return this->impl->scene;
        }
        
        
        void SceneManager::render() {
            assert(this->impl != nullptr);
            
            if (this->impl->renderer == nullptr) {
                throw std::runtime_error("SceneManager::render: "
                                         "A non null renderer must be used");
            }
            
            if (this->impl->scene == nullptr) {
                throw std::runtime_error("SceneManager::render: "
                                         "Must have a scene to render.");
            }
            
            this->impl->renderer->renderScene(this->impl->scene);
        }
    }
}
