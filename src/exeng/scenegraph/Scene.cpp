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

#include <list>
#include <exeng/math/TVector.hpp>
#include <exeng/scenegraph/Scene.hpp>
#include <exeng/scenegraph/SceneNode.hpp>
#include <exeng/scenegraph/Camera.hpp>
#include <exeng/scenegraph/Light.hpp>

using namespace exeng;
using namespace exeng::graphics;
using namespace exeng::scenegraph;
using namespace exeng::math;

namespace exeng { namespace scenegraph {
    struct Scene::Private {
        SceneNode *rootNode;
        Color backColor;
        
        SceneNodes cameraNodes;
        SceneNodes lightNodes;
        
        Private() {
            this->rootNode = new SceneNode("rootNode");
        }
        
        ~Private() {
            delete this->rootNode;
        }
    };
    
    
    Scene::Scene() : impl(nullptr) {
        this->impl = new Scene::Private();
    }


    Scene::~Scene() {
        delete this->impl;
    }
    
    
    SceneNode* Scene::getRootNode() {
        return this->impl->rootNode;
    }

    const SceneNode* Scene::getRootNode() const {
        return this->impl->rootNode;
    }
    
    
    SceneNode* Scene::addCamera(Camera *camera, const std::string &name) {
        assert(this->impl != nullptr);
        
        return this->addCamera(camera, name, this->getRootNode());
    }
    
    
    SceneNode* Scene::addCamera(Camera *camera, const std::string &name, SceneNode *parent) {
        assert(this->impl != nullptr);
        
        SceneNode *cameraNode = nullptr;
        
        cameraNode = new SceneNode();
        cameraNode->setName(name);
        cameraNode->setParent(parent);
        cameraNode->setData(camera);
        
        this->impl->cameraNodes.push_back(cameraNode);
        
        return cameraNode;
    }
    
    
    const SceneNodes& Scene::getCameraSceneNodes() const {
        assert(this->impl != nullptr);
        return this->impl->cameraNodes;
    }
    
    
    SceneNode* Scene::addLight(Light *light, const std::string &name) {
        assert(this->impl != nullptr);
        
        return this->addLight(light, name, this->getRootNode());
    }
    
    
    SceneNode* Scene::addLight(Light *light, const std::string &name, SceneNode *parent) {
        assert(this->impl != nullptr);
        
        SceneNode *lightNode = nullptr;
        
        lightNode = new SceneNode();
        lightNode->setName(name);
        lightNode->setParent(parent);
        lightNode->setData(light);

        this->impl->lightNodes.push_back(lightNode);        
        
        return lightNode;
    }
    
    
    const SceneNodes& Scene::getLightSceneNodes() const {
        assert(this->impl != nullptr);
        
        return this->impl->lightNodes;
    }
    
    
    void Scene::setBackColor(const Color &color){
        assert(this->impl != nullptr);
        
        this->impl->backColor = color;
    }


    Color Scene::getBackColor() const{
        assert(this->impl != nullptr);
        
        return this->impl->backColor;
    }
}}
