
#ifndef __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__
#define __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__

#include <stack>
#include <functional>
#include <exeng/Exception.hpp>
#include <exeng/Matrix.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/graphics/MeshSubset.hpp>
#include <exeng/scenegraph/SceneRenderer.hpp>
#include <exeng/scenegraph/SceneNode.hpp>
#include <exeng/scenegraph/Mesh.hpp>

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

	/*
	class NodeRenderer {
	public:
		setTransform(Matrix4f);
		renderNodeData(SceneNodeData);
		prepareCamera(Camera);
	};
	*/

	class GraphicsNodeRenderer {
	public:
		GraphicsNodeRenderer() {}
		~GraphicsNodeRenderer() {}

		void setTransformName(const std::string &transformName) {
			this->transformName = transformName;
		}

		void setGraphicsDriver(exeng::graphics::GraphicsDriver *driver) {
			this->driver = driver;
		}

		exeng::graphics::GraphicsDriver* getGraphicsDriver() {
			return this->driver;
		}

		const exeng::graphics::GraphicsDriver* getGraphicsDriver() const {
			return this->driver;
		}

		void setTransform(const Matrix4f &transform) {
			this->transform = transform;
		}

		void prepareCamera(const exeng::scenegraph::Camera *camera) {
		
		}

		void renderNodeData(const exeng::scenegraph::SceneNodeData *data) {
			TypeInfo info = data->getTypeInfo();

			if (info == TypeId<Mesh>()) {
				const exeng::scenegraph::Mesh *mesh = static_cast<const exeng::scenegraph::Mesh*>(data);

				for (int i=0; i<mesh->getSubsetCount(); ++i) {
					const exeng::graphics::MeshSubset *subset = mesh->getSubset(i);

					this->driver->setMaterial(subset->getMaterial());
					this->driver->setMeshSubset(subset);
					this->driver->getModernModule()->setProgramGlobal(this->transformName, this->transform);
					this->driver->render(subset->getPrimitive(), subset->getVertexCount());
				}
			} else {
				EXENG_THROW_EXCEPTION("Unsupported Geometry type.");
			}
		}

	private:
		std::string transformName;
		exeng::graphics::GraphicsDriver* driver = nullptr;
		Matrix4f transform;
	};

	template <typename NodeRenderer>
	class GenericSceneRenderer : public SceneRenderer, public NodeRenderer {
	public:

		GenericSceneRenderer() {
		}

		virtual void setScene(const Scene *scene) {
			this->scene = scene;
		}

		virtual const Scene* getScene() const override {
			return this->scene;
		}

		virtual void render(const Camera *camera) override {
			Vector3f position = camera->getPosition();
			Vector3f lookAt = camera->getLookAt();
			Vector3f up = camera->getUp();

			Matrix4f vpMatrix = identity<float, 4>();

			// TODO: Retrieve perspective information from camera
			vpMatrix *= perspective<float>(rad(60.0f), 1.33333f, 0.1f, 1000.0f);
			vpMatrix *= lookat<float>(position, lookAt, up);
			
			NodeRenderer::prepareCamera(camera);
			this->transformStack.init(vpMatrix);
			this->renderNode(this->getScene()->getRootNode());
		}

	private:
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

			NodeRenderer::setTransform(this->transformStack.top());
			if (node->getData()) {
				NodeRenderer::renderNodeData(node->getData());
			}

			// render hierarchy
			for (SceneNode *child : node->getChilds()) {
				this->renderNode(child);
			}

			this->transformStack.pop();
		}

	private:
		TransformStack<Matrix4f> transformStack;
		const Scene* scene = nullptr;
	};
}}

#endif  // __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__
