/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "../math/TVector.hpp"
#include "Scene.hpp"
#include "SceneNode.hpp"
#include "Camera.hpp"
#include "Light.hpp"

using exeng::graphics::Color;
using exeng::scenegraph::SceneNode;

struct exeng::scenegraph::Scene::Private {
    SceneNode *rootNode;
    Color backColor;
    
    Private() {
        this->rootNode = new SceneNode("");
    }
};


namespace exeng {
    namespace scenegraph {
        Scene::Scene() {
            this->impl = new Scene::Private();
        }
        
        
        Scene::~Scene() {
            delete this->impl;
        }
        
        
        auto Scene::getRootNodePtr() -> SceneNode* {
            return this->impl->rootNode;
        }
        
        
        auto Scene::addCamera(Camera *camera) -> SceneNode* {
            SceneNode *cameraNode = nullptr;
            
            cameraNode = this->getRootNodePtr()->addChildPtr("");
            cameraNode->setDataPtr(camera);
            
            return cameraNode;
        }
        
        
        auto Scene::addLight(Light *light)  -> SceneNode* {
            SceneNode *lightNode = nullptr;
            
            lightNode = this->getRootNodePtr()->addChildPtr("");
            lightNode->setDataPtr(light);
            
            return lightNode;
        }
        
        
        auto Scene::setBackgroundColor(const Color &color) -> void  {
            this->impl->backColor = color;
        }
        
        
        auto Scene::getBackgroundColor() const -> Color  {
            return this->impl->backColor;
        }
    }
}
