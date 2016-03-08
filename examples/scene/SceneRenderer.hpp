
#pragma once 

#ifndef __xe_scene_scenerenderer_hpp__
#define __xe_scene_scenerenderer_hpp__

#include <xe/sg/IRenderer.hpp>
#include <xe/sg/ISceneRenderer.hpp>
#include <xe/sg/TransformationStack.hpp>

class SceneRenderer : public xe::sg::ISceneRenderer {
public:
	SceneRenderer() {}
	explicit SceneRenderer(xe::sg::IRenderer *renderer);
	virtual ~SceneRenderer() {}

public:
	virtual void setScene(xe::sg::Scene* scene) override;

	virtual xe::sg::Scene* getScene() override;

	virtual const xe::sg::Scene* getScene() const override;

	virtual void renderScene() override;

public:
	xe::sg::IRenderer* getRenderer();

	const xe::sg::IRenderer* getRenderer() const;

	void setRenderer(xe::sg::IRenderer* renderer);

protected:
	void renderNode(xe::sg::SceneNode* node);

private:
	xe::sg::Scene* scene = nullptr;
	xe::sg::IRenderer* renderer = nullptr;
	xe::sg::TransformationStack transformStack;
};

#endif
