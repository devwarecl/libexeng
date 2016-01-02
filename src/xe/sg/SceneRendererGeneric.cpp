//
//#include "SceneRendererGeneric.hpp"
//
//#include <xe/sg/Scene.hpp>
//
//namespace xe { namespace sg {
//	template<typename MatrixType>
//	class TransformStack {
//	public:
//		void init(const MatrixType& m) {
//			this->stack = std::stack<MatrixType>();
//			this->stack.push(m);
//		}
//
//		void push(const MatrixType& m) {
//			MatrixType current = this->top();
//			this->stack.push(current * m);
//		}
//
//		void pop() {
//			this->stack.pop();
//		}
//
//		MatrixType top() {
//			return this->stack.top();
//		}
//
//	public:
//		std::stack<MatrixType> stack;
//	};
//}}
//
//namespace xe { namespace sg {
//    Matrix4f RenderWrapper::getViewMatrix(const Camera *camera) {
//        Vector3f position = camera->getPosition();
//		Vector3f lookAt = camera->getLookAt();
//		Vector3f up = camera->getUp();
//
//		Matrix4f viewMatrix = lookat<float>(position, lookAt, up);
//
//        return viewMatrix;
//    }
//
//    Matrix4f RenderWrapper::getProjectionMatrix(const Camera *camera) {
//        // TODO: Retrieve perspective information from camera
//        return perspective<float>(rad(60.0f), 1.33333f, 0.1f, 1000.0f);	
//    }
//}}
//
//namespace xe { namespace sg {
//
//    using namespace xe::gfx;
//
//    struct RasterizerRenderWrapper::Private {
//        GraphicsDriver* driver = nullptr;
//		Matrix4f transform;
//        std::string transformName;
//    };
//
//	RasterizerRenderWrapper::RasterizerRenderWrapper(GraphicsDriver *driver) {
//        this->impl = new RasterizerRenderWrapper::Private();
//        this->impl->driver = driver;
//    }
//
//	RasterizerRenderWrapper::~RasterizerRenderWrapper() {
//        delete impl;
//    }
//
//	void RasterizerRenderWrapper::setTransformName(const std::string &transformName) {
//		this->impl->transformName = transformName;
//	}
//    
//	GraphicsDriver* RasterizerRenderWrapper::getGraphicsDriver() {
//		return this->impl->driver;
//	}
//
//	const GraphicsDriver* RasterizerRenderWrapper::getGraphicsDriver() const {
//		return this->impl->driver;
//	}
//        
//	void RasterizerRenderWrapper::setTransform(const Matrix4f &transform) {
//		this->impl->transform = transform;
//	}
//
//    void RasterizerRenderWrapper::beginFrame(const Vector4f &clearColor) {
//        this->getGraphicsDriver()->beginFrame(clearColor, xe::gfx::ClearFlags::ColorDepth);
//    }
//
//    void RasterizerRenderWrapper::endFrame() {
//        this->getGraphicsDriver()->endFrame();
//    }
//
//	void RasterizerRenderWrapper::renderNodeData(const xe::sg::SceneNodeData *data) {
//		assert(this);
//		assert(this->impl);
//
//		TypeInfo info = data->getTypeInfo();
//        GraphicsDriver *driver = this->impl->driver;
//
//		assert(driver);
//		assert(driver->getModernModule());
//
//		if (info == TypeId<Mesh>()) {
//			const auto mesh = static_cast<const xe::gfx::Mesh*>(data);
//
//			assert(mesh);
//
//			for (int i=0; i<mesh->getSubsetCount(); ++i) {
//				const xe::gfx::MeshSubset *subset = mesh->getSubset(i);
//
//				assert(mesh);
//
//				driver->setMaterial(subset->getMaterial());
//				driver->setMeshSubset(subset);
//				driver->getModernModule()->setProgramGlobal(this->impl->transformName, this->impl->transform);
//				driver->render(subset->getPrimitive(), subset->getVertexCount());
//			}
//		} else {
//			EXENG_THROW_EXCEPTION("Unsupported Geometry type.");
//		}
//	}
//}}
//
//namespace xe { namespace sg {
//
//    struct SceneRendererGeneric::Private {
//        TransformStack<Matrix4f> transformStack;
//        RenderWrapperPtr renderWrapper;
//        const Scene* scene = nullptr;
//
//        /**
//		 * @brief Render a complete SceneNode hierarchy
//		 */
//	    void renderNode(const SceneNode *node) {
//#if defined(EXENG_DEBUG)
//		    if (node == nullptr) {
//			    EXENG_THROW_EXCEPTION("The node object can't be a null pointer.");
//		    }
//#endif
//		    this->transformStack.push(node->getTransform());
//
//		    this->renderWrapper->setTransform(this->transformStack.top());
//
//		    if (node->getData()) {
//			    this->renderWrapper->renderNodeData(node->getData());
//		    }
//
//		    // render hierarchy
//		    for (SceneNode *child : node->getChilds()) {
//			    this->renderNode(child);
//		    }
//
//		    this->transformStack.pop();
//	    }
//    };
//
//    SceneRendererGeneric::SceneRendererGeneric(RenderWrapperPtr renderWrapper) {
//        this->impl = new SceneRendererGeneric::Private();
//        this->impl->renderWrapper = std::move(renderWrapper);
//    }
//
//    SceneRendererGeneric::~SceneRendererGeneric() {
//        delete this->impl;
//    }
//
//    RenderWrapper* SceneRendererGeneric::getRenderWrapper() {
//        return this->impl->renderWrapper.get();
//    }
//
//    const RenderWrapper* SceneRendererGeneric::getRenderWrapper() const {
//        return this->impl->renderWrapper.get();
//    }
//
//	void SceneRendererGeneric::setScene(const Scene *scene) {
//		this->impl->scene = scene;
//	}
//
//	const Scene* SceneRendererGeneric::getScene() const {
//		return this->impl->scene;
//	}
//
//	void SceneRendererGeneric::render(const Camera *camera) {
//        RenderWrapper *renderWrapper = this->getRenderWrapper();
//
//        renderWrapper->beginFrame(this->getScene()->getBackColor());
//
//        renderWrapper->prepareCamera(camera);
//
//        Matrix4f projMatrix = renderWrapper->getProjectionMatrix(camera);
//        Matrix4f viewMatrix = renderWrapper->getViewMatrix(camera);
//
//		// Build the modelview matrix
//        Matrix4f vpMatrix = identity<float, 4>();
//		vpMatrix *= projMatrix;
//		vpMatrix *= viewMatrix;
//			
//        // Render the scene graph, from the root node
//		this->impl->transformStack.init(vpMatrix);
//		this->impl->renderNode(this->getScene()->getRootNode());
//
//        renderWrapper->endFrame();
//	}
//}}
