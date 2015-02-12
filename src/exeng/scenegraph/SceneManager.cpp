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

#include "SceneManager.hpp"

#include <cassert>
#include <stdexcept>
#include <string>
#include <list>
#include <exeng/scenegraph/SceneRenderer.hpp>

namespace exeng { namespace scenegraph {

    struct SceneManager::Private {
        Root *root = nullptr;
        SceneRenderer *renderer = nullptr;
        Scene *scene = nullptr;
        
        Private(Root *root_) 
        {
            this->root = root_;
        }
    };
    
    SceneManager::SceneManager(Root *root) : impl() 
    {
        this->impl = new SceneManager::Private(root);
        this->impl->root = root;
    }
    
    const Root* SceneManager::getRoot() const 
    {
        assert(this->impl != nullptr);
        return this->impl->root;
    }
    
    Root* SceneManager::getRoot() 
    {
        assert(this->impl != nullptr);
        return this->impl->root;
    }
    
    void SceneManager::setSceneRenderer(SceneRenderer *renderer) 
    {
        assert(this->impl != nullptr);
        this->impl->renderer = renderer;
    }
    
    SceneRenderer* SceneManager::getSceneRenderer() 
    {
        assert(this->impl != nullptr);
        return this->impl->renderer;
    }
    
    const SceneRenderer* SceneManager::getSceneRenderer() const 
    {
        assert(this->impl != nullptr);
        return this->impl->renderer;
    }
    
    void SceneManager::setScene(Scene *scene) 
    {
        assert(this->impl != nullptr);
        this->impl->scene = scene;
    }
    
    Scene* SceneManager::getScene() 
    {
        assert(this->impl != nullptr);
        return this->impl->scene;
    }
    
    const Scene* SceneManager::getScene() const 
    {
        assert(this->impl != nullptr);
        return this->impl->scene;
    }
    
    void SceneManager::render(const Camera *camera) 
    {
        assert(this->impl != nullptr);
        
        if (this->impl->renderer == nullptr) {
            throw std::runtime_error("SceneManager::render: non null renderer must be used");
        }
        
        if (this->impl->scene == nullptr) {
            throw std::runtime_error("SceneManager::render: Must have a scene to render.");
        }
        
        this->impl->renderer->setScene(this->impl->scene);
        this->impl->renderer->renderScene(camera);
    }
}}
