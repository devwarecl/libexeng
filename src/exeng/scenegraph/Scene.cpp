
#include "../math/TVector.hpp"
#include "Scene.hpp"
#include "SceneNode.hpp"
#include "Camera.hpp"
#include "Light.hpp"

struct exeng::scenegraph::Scene::Private
{
    exeng::scenegraph::SceneNode *rootNode;
    exeng::math::Vector4f backColor;
    
    Private()
    {
        this->rootNode = new exeng::scenegraph::SceneNode("");
    }
};


namespace exeng
{
    namespace scenegraph
    {
        Scene::Scene()
        {
            this->impl = new Scene::Private();
        }
        
        
        Scene::~Scene()
        {
            delete this->impl;
        }
        
        
        auto Scene::getRootNodePtr() -> SceneNode*
        {
            return this->impl->rootNode;
        }
        
        
        auto Scene::addCamera(Camera *camera) -> SceneNode*
        {
            SceneNode *cameraNode = NULL;
            
            cameraNode = this->getRootNodePtr()->addChildPtr("");
            cameraNode->setDataPtr(camera);
            
            return cameraNode;
        }
        
        
        auto Scene::addLight(Light *light)  -> SceneNode*
        {
            SceneNode *lightNode = NULL;
            
            lightNode = this->getRootNodePtr()->addChildPtr("");
            lightNode->setDataPtr(light);
            
            return lightNode;
        }
        
        
        auto Scene::setBackgroundColor(const math::Vector4f &color) -> void 
        {
            this->impl->backColor = color;
        }
        
        
        auto Scene::getBackgroundColor() const -> math::Vector4f 
        {
            return this->impl->backColor;
        }
    }
}
