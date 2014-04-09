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
#include <list>
#include <exeng/scenegraph/SceneManager.hpp>
#include <exeng/scenegraph/ISceneRenderer.hpp>
// #include <exeng/graphics/Material.hpp>

namespace exeng { namespace scenegraph {

    struct SceneManager::Private {
        Root *root;
        ISceneRenderer *renderer;
        Scene *scene;
        
        Private(Root *root) : root(root), renderer(nullptr), scene(nullptr) {}
        
        ~Private() {}
    };
    
    
    SceneManager::SceneManager(Root *root) : impl(new SceneManager::Private(root)) {
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
    
    
    void SceneManager::render(const Camera *camera) {
        assert(this->impl != nullptr);
        
        if (this->impl->renderer == nullptr) {
            throw std::runtime_error("SceneManager::render: non null renderer must be used");
        }
        
        if (this->impl->scene == nullptr) {
            throw std::runtime_error("SceneManager::render: Must have a scene to render.");
        }
        
        this->impl->renderer->renderScene(this->impl->scene, camera);
    }
    
    /*
    exeng::graphics::Material *SceneManager::createMaterial() {
        assert(this->impl != nullptr);
        
        exeng::graphics::Material *material = new exeng::graphics::Material();
        this->impl->materials.push_back(material);
        return material;
    }
    
    
    exeng::graphics::Material *SceneManager::createMaterial(const std::string &name) {
        assert(this->impl != nullptr);
        
        exeng::graphics::Material *material = new exeng::graphics::Material();
        material->setName(name);
        this->impl->materials.push_back(material);
        return material;
    }
    */
}}
