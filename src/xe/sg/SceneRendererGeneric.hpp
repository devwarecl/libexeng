
#pragma once 

#ifndef __xe_sg_scenerenderergeneric_hpp__
#define __xe_sg_scenerenderergeneric_hpp__

#include <xe/sg/Renderer.hpp>
#include <xe/sg/SceneRenderer.hpp>
#include <xe/sg/TransformationStack.hpp>

namespace xe { namespace sg {
	class EXENGAPI SceneRendererGeneric : public xe::sg::SceneRenderer {
	public:
		SceneRendererGeneric() {}
		explicit SceneRendererGeneric(xe::sg::Renderer *renderer);
		virtual ~SceneRendererGeneric() {}

	public:
		virtual void setScene(xe::sg::Scene* scene) override;

		virtual xe::sg::Scene* getScene() override;

		virtual const xe::sg::Scene* getScene() const override;

		virtual void renderScene() override;

	public:
		xe::sg::Renderer* getRenderer();

		const xe::sg::Renderer* getRenderer() const;

		void setRenderer(xe::sg::Renderer* renderer);

	protected:
		void renderNode(xe::sg::TransformationStack *transformStack, xe::sg::SceneNode* node);

	private:
		xe::sg::Scene* scene = nullptr;
		xe::sg::Renderer* renderer = nullptr;
	};

}}
#endif
