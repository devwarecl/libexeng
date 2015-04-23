///**
// * @file SceneManager.hpp
// * @brief Implementation of the class SceneManager class.
// */
//
//
///*
// * Copyright (c) 2013 Felipe Apablaza.
// *
// * The license and distribution terms for this file may be
// * found in the file LICENSE in this distribution.
// */
//
//
//#include "SceneManager.hpp"
//
//#include <memory>
//#include <cassert>
//#include <string>
//#include <list>
//#include <exeng/Exception.hpp>
//#include <exeng/scenegraph/SceneRenderer.hpp>
//
//namespace exeng { namespace scenegraph {
//
//    struct SceneManager::Private {
//        std::unique_ptr<SceneRenderer> renderer;
//		std::list<SceneNodeAnimator*> animators;
//
//		Scene* scene = nullptr;
//    };
//    
//	SceneManager::SceneManager(Scene *scene) {
//		this->impl = new SceneManager::Private();
//		this->impl->scene = scene;
//	}
//
//    void SceneManager::setSceneRenderer(std::unique_ptr<SceneRenderer> renderer) {
//        assert(this->impl != nullptr);
//        this->impl->renderer = std::move(renderer);
//		this->impl->renderer->setScene(this->getScene());
//    }
//    
//    SceneRenderer* SceneManager::getSceneRenderer() {
//        assert(this->impl != nullptr);
//        return this->impl->renderer.get();
//    }
//    
//    const SceneRenderer* SceneManager::getSceneRenderer() const {
//        assert(this->impl != nullptr);
//        return this->impl->renderer.get();
//    }
//    
//    Scene* SceneManager::getScene() {
//        assert(this->impl != nullptr);
//        return this->impl->scene;
//    }
//    
//    const Scene* SceneManager::getScene() const {
//        assert(this->impl != nullptr);
//        return this->impl->scene;
//    }
//    
//	void SceneManager::addAnimator(SceneNodeAnimator *animator) {
//		assert(this->impl != nullptr);
//		this->impl->animators.push_back(animator);
//	}
//
//	void SceneManager::removeAnimator(SceneNodeAnimator *animator) {
//		assert(this->impl != nullptr);
//		this->impl->animators.remove(animator);
//	}
//
//	void SceneManager::update(double seconds) {
//		assert(this->impl != nullptr);
//
//		for (SceneNodeAnimator *animator : this->impl->animators) {
//			animator->update(seconds);
//		}
//	}
//
//    void SceneManager::render(const Camera *camera) {
//        assert(this->impl != nullptr);
//        
//        if (this->impl->renderer == nullptr) {
//            EXENG_THROW_EXCEPTION("SceneManager::render: Must have a renderer.");
//        }
//        
//        if (this->impl->scene == nullptr) {
//            EXENG_THROW_EXCEPTION("SceneManager::render: Must have a scene to render.");
//        }
//        
//		if (camera == nullptr) {
//			EXENG_THROW_EXCEPTION("SceneManager::render: Must specify a valid camera.");
//		}
//
//        this->impl->renderer->setScene(this->getScene());
//        this->impl->renderer->renderScene(camera);
//    }
//}}
