//
//#ifndef __RAYTRACER_TRACERS_MULTIHARDWARETRACER_HPP__
//#define __RAYTRACER_TRACERS_MULTIHARDWARETRACER_HPP__
//
//#include <exeng/Exeng.hpp>
//#include <memory>
//#include <stack>
//
//#include "Tracer.hpp"
//#include "../samplers/Sampler.hpp"
//
//#include <CL/cl.h>
//#include <CL/cl_gl.h>
//
//#undef CL_VERSION_1_2
//#include <CL/cl.hpp>
//#include <GLFW/glfw3.h>
//
//#if defined (EXENG_UNIX)
//#  include <GL/glx.h>
//#endif
//
//namespace raytracer { namespace tracers {
//	class MultiHardwareTracer : public Tracer {
//	public:
//		MultiHardwareTracer(const xe::sg::Scene *scene, const raytracer::samplers::Sampler *sampler);
//		virtual void render(const xe::sg::Camera *camera);
//		~MultiHardwareTracer();
//
//		virtual void setRenderTarget(xe::gfx::Texture *renderTarget);
//
//	private:
//        void syncLocalTransform(const xe::Matrix4f &localTransform);
//        
//		void executeGetStructuresSizeKernel();
//        void executeClearSynthBufferKernel();
//        
//        // void executeGenerateRaysKernelFromMatrix(const xe::sg::Camera *camera);
//        void executeGenerateRaysKernel(const xe::sg::Camera *camera);
//		void executeSynthetizeImageKernel();
//
//		void synthetize();
//
//		void executeComputeSynthesisDataKernel(std::stack<xe::Matrix4f> &transformStack, const xe::sg::SceneNode *sceneNode);
//
//	private:
//		cl::Platform platform;
//		cl::Device device;
//		cl::Context context;
//
//		cl::Program program;
//		cl::Image2DGL image;
//
//        cl::Kernel clearSynthBufferKernel;
//		cl::Kernel rayGeneratorKernel;
//		cl::Kernel rayGeneratorFromMatrixKernel;
//		cl::Kernel synthesisDataComputerKernel;
//		cl::Kernel imageSynthetizerKernel;
//
//        std::vector<xe::sg::Ray> raysData;
//        
//		cl::Buffer raysBuffer;
//		cl::Buffer synthesisBuffer;
//
//		cl::Buffer samplesBuffer;
//		cl::CommandQueue queue;
//        cl::Buffer materialBuffer;
//
//		cl_int samplesCount = 0;
//
//		cl_int synthesisElementSize = 0;
//		cl_int raySize = 0;
//		
//		// TODO: Determine the appropiate range at run-time
//		cl::NDRange localSize = cl::NDRange(16, 8);	
//        
//        cl::Buffer localTransformBuffer;
//	};
//}}
//
//#endif // __RAYTRACER_TRACERS_TRACER_HPP__
