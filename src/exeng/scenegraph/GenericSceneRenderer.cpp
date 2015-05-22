
#include "GenericSceneRenderer.hpp"

#include <exeng/scenegraph/Scene.hpp>

namespace exeng { namespace scenegraph {
	template<typename MatrixType>
	class TransformStack {
	public:
		void init(const MatrixType& m) {
			this->stack = std::stack<MatrixType>();
			this->stack.push(m);
		}

		void push(const MatrixType& m) {
			MatrixType current = this->top();
			this->stack.push(current * m);
		}

		void pop() {
			this->stack.pop();
		}

		MatrixType top() {
			return this->stack.top();
		}

	public:
		std::stack<MatrixType> stack;
	};
}}

namespace exeng { namespace scenegraph {
    Matrix4f RenderWrapper::getViewMatrix(const Camera *camera) {
        Vector3f position = camera->getPosition();
		Vector3f lookAt = camera->getLookAt();
		Vector3f up = camera->getUp();

		Matrix4f viewMatrix = lookat<float>(position, lookAt, up);

        return viewMatrix;
    }

    Matrix4f RenderWrapper::getProjectionMatrix(const Camera *camera) {
        // TODO: Retrieve perspective information from camera
        return perspective<float>(rad(60.0f), 1.33333f, 0.1f, 1000.0f);	
    }
}}

namespace exeng { namespace scenegraph {

    using namespace exeng::graphics;

    struct RasterizerRenderWrapper::Private {
        GraphicsDriver* driver = nullptr;
		Matrix4f transform;
        std::string transformName;
    };

	RasterizerRenderWrapper::RasterizerRenderWrapper(GraphicsDriver *driver) {
        this->impl = new RasterizerRenderWrapper::Private();
        this->impl->driver = driver;
    }

	RasterizerRenderWrapper::~RasterizerRenderWrapper() {
        delete impl;
    }

	void RasterizerRenderWrapper::setTransformName(const std::string &transformName) {
		this->impl->transformName = transformName;
	}
    
	GraphicsDriver* RasterizerRenderWrapper::getGraphicsDriver() {
		return this->impl->driver;
	}

	const GraphicsDriver* RasterizerRenderWrapper::getGraphicsDriver() const {
		return this->impl->driver;
	}
        
	void RasterizerRenderWrapper::setTransform(const Matrix4f &transform) {
		this->impl->transform = transform;
	}

    void RasterizerRenderWrapper::beginFrame(const Vector4f &clearColor) {
        this->getGraphicsDriver()->beginFrame(clearColor, exeng::graphics::ClearFlags::ColorDepth);
    }

    void RasterizerRenderWrapper::endFrame() {
        this->getGraphicsDriver()->endFrame();
    }

	void RasterizerRenderWrapper::renderNodeData(const exeng::scenegraph::SceneNodeData *data) {
		TypeInfo info = data->getTypeInfo();
        GraphicsDriver *driver = this->impl->driver;

		if (info == TypeId<Mesh>()) {
			const exeng::scenegraph::Mesh *mesh = static_cast<const exeng::scenegraph::Mesh*>(data);

			for (int i=0; i<mesh->getSubsetCount(); ++i) {
				const exeng::graphics::MeshSubset *subset = mesh->getSubset(i);

				driver->setMaterial(subset->getMaterial());
				driver->setMeshSubset(subset);
				driver->getModernModule()->setProgramGlobal(this->impl->transformName, this->impl->transform);
				driver->render(subset->getPrimitive(), subset->getVertexCount());
			}
		} else {
			EXENG_THROW_EXCEPTION("Unsupported Geometry type.");
		}
	}
}}

namespace exeng { namespace scenegraph {

    struct GenericSceneRenderer::Private {
        TransformStack<Matrix4f> transformStack;
        RenderWrapperPtr renderWrapper;
        const Scene* scene = nullptr;

        /**
		 * @brief Render a complete SceneNode hierarchy
		 */
	    void renderNode(const SceneNode *node) {
#if defined(EXENG_DEBUG)
		    if (node == nullptr) {
			    EXENG_THROW_EXCEPTION("The node object can't be a null pointer.");
		    }
#endif
		    this->transformStack.push(node->getTransform());

		    this->renderWrapper->setTransform(this->transformStack.top());

		    if (node->getData()) {
			    this->renderWrapper->renderNodeData(node->getData());
		    }

		    // render hierarchy
		    for (SceneNode *child : node->getChilds()) {
			    this->renderNode(child);
		    }

		    this->transformStack.pop();
	    }
    };

    GenericSceneRenderer::GenericSceneRenderer(RenderWrapperPtr renderWrapper) {
        this->impl = new GenericSceneRenderer::Private();
        this->impl->renderWrapper = std::move(renderWrapper);
    }

    GenericSceneRenderer::~GenericSceneRenderer() {
        delete this->impl;
    }

    RenderWrapper* GenericSceneRenderer::getRenderWrapper() {
        return this->impl->renderWrapper.get();
    }

    const RenderWrapper* GenericSceneRenderer::getRenderWrapper() const {
        return this->impl->renderWrapper.get();
    }

	void GenericSceneRenderer::setScene(const Scene *scene) {
		this->impl->scene = scene;
	}

	const Scene* GenericSceneRenderer::getScene() const {
		return this->impl->scene;
	}

	void GenericSceneRenderer::render(const Camera *camera) {
        RenderWrapper *renderWrapper = this->getRenderWrapper();

        renderWrapper->beginFrame(this->getScene()->getBackColor());

        renderWrapper->prepareCamera(camera);

        Matrix4f projMatrix = renderWrapper->getProjectionMatrix(camera);
        Matrix4f viewMatrix = renderWrapper->getViewMatrix(camera);

		// Build the modelview matrix
        Matrix4f vpMatrix = identity<float, 4>();
		vpMatrix *= projMatrix;
		vpMatrix *= viewMatrix;
			
        // Render the scene graph, from the root node
		this->impl->transformStack.init(vpMatrix);
		this->impl->renderNode(this->getScene()->getRootNode());

        renderWrapper->endFrame();
	}
}}
