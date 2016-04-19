
#pragma once 

#ifndef __xe_sg_scenerenderergeneric_hpp__
#define __xe_sg_scenerenderergeneric_hpp__

#include <xe/sg/Pipeline.hpp>
#include <xe/sg/SceneRenderer.hpp>
#include <xe/sg/TransformationStack.hpp>

namespace xe { namespace sg {
	class EXENGAPI SceneRendererGeneric : public xe::sg::SceneRenderer {
	public:
		SceneRendererGeneric() {}
		explicit SceneRendererGeneric(xe::sg::Pipeline *renderer);
		virtual ~SceneRendererGeneric() {}

	public:
		virtual void setScene(xe::sg::Scene* scene) override;

		virtual xe::sg::Scene* getScene() override;

		virtual const xe::sg::Scene* getScene() const override;

		virtual void renderScene() override;

	public:
		xe::sg::Pipeline* getRenderer();

		const xe::sg::Pipeline* getRenderer() const;

		void setRenderer(xe::sg::Pipeline* renderer);

	protected:
		void renderNode(xe::sg::TransformationStack *transformStack, xe::sg::SceneNode* node);

	private:
		xe::sg::Scene* scene = nullptr;
		xe::sg::Pipeline* renderer = nullptr;
	};
}}

#endif
