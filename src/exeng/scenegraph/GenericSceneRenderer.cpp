
#include "GenericSceneRenderer.hpp"

#include <cassert>
#include <stack>
#include <exeng/Matrix.hpp>
#include <exeng/scenegraph/Scene.hpp>
#include <exeng/scenegraph/Mesh.hpp>

#include <map>
#include <functional>

namespace exeng { namespace scenegraph {
    
    using namespace exeng::graphics;
    
    struct GenericSceneRenderer::Impl 
    {
        GraphicsDriver *graphicsDriver = nullptr;
        const Scene* scene = nullptr;
        
        typedef std::function<void(const SceneNodeData *data)> RendererFunction;
        
        std::map<TypeInfo, RendererFunction> renderers;
        
        Impl() 
        {
            std::map<TypeInfo, RendererFunction> renderers;
            
            // Render Mesh
            renderers[TypeId<Mesh>()] = [this](const SceneNodeData *data) {
                
                const Mesh *mesh = static_cast<const Mesh*>(data);
            
                for (int i=0; i<mesh->getMeshSubsetCount(); ++i) {
                    const MeshSubset *subset = mesh->getMeshSubset(i);
                    
                    Primitive::Enum primitive = subset->getPrimitive();
                
                    int bufferSize = subset->getSize();
                    int vertexSize = subset->getVertexFormat().getSize();
                    int count = bufferSize / vertexSize;
                    
                    this->graphicsDriver->setMaterial(subset->getMaterial());
                    this->graphicsDriver->setMeshSubset(subset);
                    this->graphicsDriver->render(primitive, count);
                }
            };
            
            this->renderers = renderers;
        }
        
        /**
         * @brief Recursively render a scene node.
         */
        void renderSceneNode(std::stack<Matrix4f> *matrixStack, const SceneNode *node) 
        {
            if (node == nullptr) {
                return;
            }
            
            Matrix4f matrix = matrixStack->top();
            
            // render node content (if any)
            if (node->getData() != nullptr) {
                auto rendererIt = this->renderers.find(node->getData()->getTypeInfo());
                
                if (rendererIt != this->renderers.end()) {
                    this->graphicsDriver->setTransform(Transform::World, matrix);
                    rendererIt->second(node->getData());
                }
            }
            
            // render node childs
            for (const SceneNode *child : node->getChilds()) {
                Matrix4f childMatrix = matrixStack->top() * child->getTransform();
                
                matrixStack->push(childMatrix);
                this->renderSceneNode(matrixStack, child);
                matrixStack->pop();
            }
        }
    };
    
    GenericSceneRenderer::GenericSceneRenderer(GraphicsDriver *graphicsDriver) 
    {
#if defined(EXENG_DEBUG)
        if (graphicsDriver == nullptr) {
            throw std::runtime_error("GenericSceneRenderer::GenericSceneRenderer: Invalid supplied graphics driver.");
        }
#endif
        this->impl = new GenericSceneRenderer::Impl();
        
        this->impl->graphicsDriver = graphicsDriver;
    }

    GenericSceneRenderer::~GenericSceneRenderer() 
    {
        delete this->impl;
    }

    const Scene* GenericSceneRenderer::getScene() const
    {
        assert(this->impl != nullptr);
        
        return this->impl->scene;
    }
    
    void GenericSceneRenderer::setScene(const Scene *scene) 
    {
        assert(this->impl != nullptr);
        
        this->impl->scene = scene;
    }

    void GenericSceneRenderer::renderScene(const Camera *camera) 
    {
        assert(this->impl != nullptr);
        
        // Fetch members
        const Scene* scene = this->impl->scene;
        GraphicsDriver *graphicsDriver = this->impl->graphicsDriver;
        
        // 
        graphicsDriver->beginFrame(scene->getBackColor(), ClearFlags::Color|ClearFlags::Depth);
        
        std::stack<Matrix4f> matrixStack;
        
        matrixStack.push(scene->getRootNode()->getTransform());
        this->impl->renderSceneNode(&matrixStack, scene->getRootNode());
        matrixStack.pop();  // for simmetry
        
        graphicsDriver->endFrame();
    }
}}
