
/**
 * @file Scene.cpp
 * @brief Scene class implementation.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "Scene.hpp"

#include <xe/Vector.hpp>
#include <xe/sg/SceneNode.hpp>

namespace xe { namespace sg {
    using namespace xe;
    using namespace xe::gfx;

    struct Scene::Private {
        Vector4f backColor = {0.0f, 0.0f, 0.0f, 1.0f};
        SceneNodePtr rootNode = std::make_unique<SceneNode>();
    };
    
    Scene::Scene() {
		impl = new Scene::Private();
	}

    Scene::~Scene() {
		delete impl;
	}
    
    SceneNode* Scene::getRootNode() {
        assert(impl);
        return impl->rootNode.get();
    }

    const SceneNode* Scene::getRootNode() const {
        assert(impl);
        return impl->rootNode.get();
    }
    
    void Scene::setBackColor(const Vector4f &color) {
        assert(impl);
        impl->backColor = color;
    }

    Vector4f Scene::getBackColor() const {
        assert(impl);
        return impl->backColor;
    }
}}
