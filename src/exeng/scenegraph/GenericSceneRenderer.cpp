
#include "GenericSceneRenderer.hpp"

//#include <cassert>
//#include <stack>
//#include <exeng/Matrix.hpp>
//#include <exeng/scenegraph/Scene.hpp>
//#include <exeng/scenegraph/Mesh.hpp>
//
//#include <map>
//#include <functional>
//
//namespace exeng { namespace scenegraph {
//    using namespace exeng::graphics;
//
//    /**
//     * @brief Recursively render a scene node.
//     */
//    void GenericSceneRenderer::renderSceneNode(std::stack<Matrix4f> *matrixStack, const SceneNode *node) 
//    {
//        if (node == nullptr) {
//            return;
//        }
//        
//        Matrix4f matrix = matrixStack->top();
//        
//        // render node content (if any)
//        if (node->getData() != nullptr) {
//			this->renderSceneNodeData(node->getData());
//        }
//            
//        // render node childs
//        for (const SceneNode *child : node->getChilds()) {
//            Matrix4f childMatrix = matrixStack->top() * child->getTransform();
//                
//            matrixStack->push(childMatrix);
//            this->renderSceneNode(matrixStack, child);
//            matrixStack->pop();
//        }
//    }
//    
//    GenericSceneRenderer::GenericSceneRenderer(GraphicsDriver *graphicsDriver) 
//    {
//#if defined(EXENG_DEBUG)
//        if (graphicsDriver == nullptr) {
//            throw std::runtime_error("GenericSceneRenderer::GenericSceneRenderer: Invalid supplied graphics driver.");
//        }
//#endif
//		this->graphicsDriver = graphicsDriver;
//
//		this->registerRenderer(TypeId<Mesh>(), [this](const SceneNodeData *data) {
//            const Mesh *mesh = static_cast<const Mesh*>(data);
//            
//            for (int i=0; i<mesh->getMeshSubsetCount(); ++i) {
//                const MeshSubset *subset = mesh->getMeshSubset(i);
//                    
//                Primitive::Enum primitive = subset->getPrimitive();
//                
//                int bufferSize = subset->getSize();
//                int vertexSize = subset->getVertexFormat().getSize();
//                int count = bufferSize / vertexSize;
//
//                this->graphicsDriver->setMaterial(subset->getMaterial());
//                this->graphicsDriver->setMeshSubset(subset);
//                this->graphicsDriver->render(primitive, count);
//            }
//		});
//    }
//
//    GenericSceneRenderer::~GenericSceneRenderer() {}
//
//    void GenericSceneRenderer::renderScene(const Camera *camera) 
//    {
//        graphicsDriver->beginFrame(this->getScene()->getBackColor(), ClearFlags::ColorDepth);
//        
//        std::stack<Matrix4f> matrixStack;
//        
//        matrixStack.push(this->getScene()->getRootNode()->getTransform());
//        this->renderSceneNode(&matrixStack, this->getScene()->getRootNode());
//        matrixStack.pop();  // for simmetry
//        
//        graphicsDriver->endFrame();
//    }
//}}
