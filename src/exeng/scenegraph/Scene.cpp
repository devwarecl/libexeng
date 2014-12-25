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

#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <exeng/Vector.hpp>
#include <exeng/scenegraph/SceneNode.hpp>
#include <exeng/scenegraph/Camera.hpp>
#include <exeng/scenegraph/Light.hpp>

namespace exeng { namespace scenegraph {
    using namespace exeng;
    using namespace exeng::graphics;
    using namespace exeng::scenegraph;

    struct Scene::Private {
        Color backColor;
        
        std::list<SceneNode*> cameraNodes;
        std::list<SceneNode*> lightNodes;
        std::unique_ptr<SceneNode> rootNode;
        
        std::list<std::unique_ptr<Light>> lights;
        std::list<std::unique_ptr<Camera>> cameras;

        std::map<std::string, std::unique_ptr<Material>> materials;
        std::list<Material*> materialList;

        Private() : rootNode(new SceneNode("rootNode")) {}
    };
    
    Scene::Scene() : impl(new Scene::Private()) {}

    Scene::~Scene() {}
    
    SceneNode* Scene::getRootNode() {
        assert(this->impl != nullptr);
        return this->impl->rootNode.get();
    }

    const SceneNode* Scene::getRootNode() const {
        assert(this->impl != nullptr);
        return this->impl->rootNode.get();
    }
    
    void Scene::setBackColor(const Color &color){
        assert(this->impl != nullptr);
        this->impl->backColor = color;
    }

    Color Scene::getBackColor() const{
        assert(this->impl != nullptr);
        return this->impl->backColor;
    }

    Camera* Scene::createCamera() {
        assert(this->impl != nullptr);

        Camera* camera = new Camera();

        this->impl->cameras.push_back(std::unique_ptr<Camera>(camera));

        return camera;
    }

    Light* Scene::createLight() {
        assert(this->impl != nullptr);

        Light* light = new Light();

        this->impl->lights.push_back(std::unique_ptr<Light>(light));
        
        return light;
    }

    Material* Scene::createMaterial(const std::string &materialName) {
        assert(this->impl != nullptr);
        
        auto material = std::unique_ptr<Material>(new Material());
        material->setName(materialName);
        
        this->impl->materials[materialName] = std::move(material);
        this->impl->materialList.push_back(material.get());

        return this->impl->materials[materialName].get();
    }

    SceneNode* Scene::createSceneNode(const std::string &nodeName, SceneNodeData* nodeData) {
        assert(this->impl != nullptr);
        
        std::list<SceneNode*> *nodes = nullptr;
        
        SceneNode *sceneNode = this->impl->rootNode->addChild(nodeName);
        sceneNode->setData(nodeData);
        
        if (nodeData->getTypeInfo() == TypeId<Camera>()) {
            nodes = &this->impl->cameraNodes;
        }
        
        if (nodeData->getTypeInfo() == TypeId<Light>()) {
            nodes = &this->impl->lightNodes;
        }
        
        if (nodes) {
            nodes->push_back(sceneNode);
        }
        
        return sceneNode;
    }

    const Material* Scene::getMaterial(const int index) const
    {
#if defined(EXENG_DEBUG)
        if (index < 0 || index >= this->getMaterialCount()) {
            std::stringstream ss;

            ss << "Scene::getMaterial: The index ";
            ss << "(" << index << ") ";
            ss << "out of bounds.";

            throw std::runtime_error(ss.str());
        }
#endif
        auto materialIterator = this->impl->materialList.begin();

        std::advance(materialIterator, index);

        return *materialIterator;
    }

    const int Scene::getMaterialCount() const
    {
        return this->impl->materials.size();
    }
}}
