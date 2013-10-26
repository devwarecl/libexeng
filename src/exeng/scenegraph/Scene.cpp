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

    Private() {
        this->rootNode = new SceneNode("");
    }
};

Scene::Scene() {
    this->impl = new Scene::Private();
}


Scene::~Scene() {
    delete this->impl;
}


SceneNode* Scene::getRootNodePtr() {
    return this->impl->rootNode;
}

const SceneNode* Scene::getRootNodePtr() const {
    return this->impl->rootNode;
}


SceneNode* Scene::addCamera(Camera *camera) {
    SceneNode *cameraNode = nullptr;
    
    cameraNode = this->getRootNodePtr()->addChildPtr("");
    cameraNode->setDataPtr(camera);
    
    return cameraNode;
}


SceneNode* Scene::addLight(Light *light) {
    SceneNode *lightNode = nullptr;
    
    lightNode = this->getRootNodePtr()->addChildPtr("");
    lightNode->setDataPtr(light);
    
    return lightNode;
}


void Scene::setBackgroundColor(const Color &color){
    this->impl->backColor = color;
}


Color Scene::getBackgroundColor() const{
    return this->impl->backColor;
}


}}
