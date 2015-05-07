
#ifndef __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__
#define __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__

#include <stack>
#include <functional>
#include <exeng/Exception.hpp>
#include <exeng/Matrix.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/scenegraph/SceneRenderer.hpp>
#include <exeng/scenegraph/SceneNode.hpp>

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
		renderNodeData(SceneNodeData)
	};
	*/

	template <typename NodeRenderer>
	class GenericSceneRenderer : public SceneRenderer, public NodeRenderer {
	public:
		virtual void setScene(const Scene *scene) {
			this->scene = scene;
		}

		virtual const Scene* getScene() const override {
			return this->scene;
		}

		virtual void render(const Camera *camera) override {
			this->transformStack.init(identity<float, 4>());
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

	//typedef std::function<void (const SceneNodeData*)> NodeRendererCallback;

 //   /**
 //    * @brief Quick'n dirty Scene Renderer.
 //    */
 //   class EXENGAPI GenericSceneRenderer : public SceneRenderer {
 //   public:
	//	/* SceneRenderer  */

 //       explicit GenericSceneRenderer(exeng::graphics::GraphicsDriver *graphicsDriver);
 //       virtual ~GenericSceneRenderer();
 //       
 //       virtual void render(const Camera *camera) override;
	//	virtual void setScene(const Scene *scene) override;
	//	virtual const Scene* getScene() const override;

	//public:
	//	void registerRenderer(TypeInfo info, NodeRendererCallback renderer);
	//	void unregisterRendrer(TypeInfo info, NodeRendererCallback renderer);

	//private:
	//	void renderNode(std::stack<Matrix4f> *matrixStack, const SceneNode *node);

	//private:
	//	struct Private;
	//	Private *impl = nullptr;
 //   };
}}

#endif  // __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__
