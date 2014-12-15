
#ifndef __RAYTRACER_TRACERS_MULTIHARDWARETRACER_HPP__
#define __RAYTRACER_TRACERS_MULTIHARDWARETRACER_HPP__

#include <exeng/Exeng.hpp>
#include <memory>

#include "Tracer.hpp"
#include "../samplers/Sampler.hpp"

namespace raytracer { namespace tracers {
	class MultiHardwareTracer : public Tracer {
	public:
		MultiHardwareTracer(const exeng::scenegraph::Scene *scene, const raytracer::samplers::Sampler *sampler);
		virtual void render(const exeng::scenegraph::Camera *camera);
		~MultiHardwareTracer();

		virtual void setRenderTarget(exeng::graphics::Texture *renderTarget);

	private:
		void executeGetStructuresSizeKernel();

        void executeClearSynthBufferKernel();
        void executeGenerateRaysKernel(const exeng::scenegraph::Camera *camera);
		void executeComputeSynthesisDataKernel();
		void executeSynthetizeImageKernel();

	private:
		struct Private;
		std::unique_ptr<Private> impl;
	};
}}

#endif // __RAYTRACER_TRACERS_TRACER_HPP__
