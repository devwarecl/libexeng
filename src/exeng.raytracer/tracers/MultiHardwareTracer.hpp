
#ifndef __RAYTRACER_TRACERS_MULTIHARDWARETRACER_HPP__
#define __RAYTRACER_TRACERS_MULTIHARDWARETRACER_HPP__

#include <exeng/Exeng.hpp>
#include <memory>
#include <stack>

#include "Tracer.hpp"
#include "../samplers/Sampler.hpp"

#include <CL/cl.h>
#include <CL/cl_gl.h>

#undef CL_VERSION_1_2
#include <CL/cl.hpp>
#include <GLFW/glfw3.h>

#if defined (EXENG_UNIX)
#  include <GL/glx.h>
#endif

namespace raytracer { namespace tracers {
	class MultiHardwareTracer : public Tracer {
	public:
		MultiHardwareTracer(const exeng::scenegraph::Scene *scene, const raytracer::samplers::Sampler *sampler);
		virtual void render(const exeng::scenegraph::Camera *camera);
		~MultiHardwareTracer();

		virtual void setRenderTarget(exeng::graphics::Texture *renderTarget);

	private:
        void syncLocalTransform(const exeng::Matrix4f &localTransform);
        
		void executeGetStructuresSizeKernel();
        void executeClearSynthBufferKernel();
        
        // void executeGenerateRaysKernelFromMatrix(const exeng::scenegraph::Camera *camera);
        void executeGenerateRaysKernel(const exeng::scenegraph::Camera *camera);
		void executeSynthetizeImageKernel();

		void synthetize();

		void executeComputeSynthesisDataKernel(std::stack<exeng::Matrix4f> &transformStack, const exeng::scenegraph::SceneNode *sceneNode);

	private:
		cl::Platform platform;
		cl::Device device;
		cl::Context context;

		cl::Program program;
		cl::Image2DGL image;

        cl::Kernel clearSynthBufferKernel;
		cl::Kernel rayGeneratorKernel;
		cl::Kernel rayGeneratorFromMatrixKernel;
		cl::Kernel synthesisDataComputerKernel;
		cl::Kernel imageSynthetizerKernel;

        std::vector<exeng::scenegraph::Ray> raysData;
        
		cl::Buffer raysBuffer;
		cl::Buffer synthesisBuffer;

		cl::Buffer samplesBuffer;
		cl::CommandQueue queue;
        cl::Buffer materialBuffer;

		cl_int samplesCount = 0;

		cl_int synthesisElementSize = 0;
		cl_int raySize = 0;
		
		// TODO: Determine the appropiate range at run-time
		cl::NDRange localSize = cl::NDRange(16, 8);	
        
        cl::Buffer localTransformBuffer;
	};
}}

#endif // __RAYTRACER_TRACERS_TRACER_HPP__
