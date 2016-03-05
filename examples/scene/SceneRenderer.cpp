
#include "SceneRenderer.hpp"

#include <cassert>
#include <xe/sg/Scene.hpp>
#include <xe/sg/SceneNode.hpp>
#include <xe/sg/SceneNodeData.hpp>
#include <xe/sg/IRenderable.hpp>

void SceneRenderer::setScene(xe::sg::Scene* scene) {
	assert(scene);
	this->scene = scene;
}

xe::sg::Scene* SceneRenderer::getScene() {
	return this->scene;
}

const xe::sg::Scene* SceneRenderer::getScene() const {
	return this->scene;
}

xe::sg::IRenderer* SceneRenderer::getRenderer() {
	return this->renderer;
}

const xe::sg::IRenderer* SceneRenderer::getRenderer() const {
	return this->renderer;
}

void SceneRenderer::setRenderer(xe::sg::IRenderer* renderer) {
	this->renderer = renderer;
}

void SceneRenderer::renderScene(xe::sg::Camera*) {
	assert(scene);

	transformStack.reset(xe::identity<float, 4>());

	this->renderNode(this->getScene()->getRootNode());
}

void SceneRenderer::renderNode(xe::sg::SceneNode* node) {
	assert(node);

	transformStack.push(node->getTransform());

	xe::sg::IRenderable *renderable = node->getRenderable();
	xe::sg::IRenderer *renderer = this->getRenderer();

	renderer->setTransformation(transformStack.top());

	if (renderable) {
		renderable->renderWith(renderer);
	}

	for (int i=0; i<node->getChildCount(); i++) {
		xe::sg::SceneNode *child = node->getChild(i);
		assert(child);
		this->renderNode(child);
	}

	transformStack.pop();
}
