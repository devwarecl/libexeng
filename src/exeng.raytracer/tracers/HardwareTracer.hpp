///**
// * @file RayTracer.hpp
// * @brief Interfaz de un trazador de rayos
// */
//
//#ifndef __RAYTRACER_TRACERS_HARDWARETRACER_HPP__
//#define __RAYTRACER_TRACERS_HARDWARETRACER_HPP__
//
//#include <exeng/Exeng.hpp>
//#include <memory>
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
//  #include <GL/glx.h>
//#endif
//
//using namespace xe;
//using namespace xe::gfx;
//using namespace xe::sg;
//
//namespace raytracer { namespace tracers {
//    class HardwareTracer : public Tracer {
//    public:
//        HardwareTracer(const xe::sg::Scene *scene, const raytracer::samplers::Sampler *sampler);
//        virtual void render(const xe::sg::Camera *camera);
//        ~HardwareTracer();
//        
//        virtual void setRenderTarget(xe::gfx::Texture *renderTarget);
//        
//    private:
//		cl::Platform platform;
//        cl::Device device;
//        cl::Context context;
//        cl::Program program;
//        cl::Image2DGL image;
//        cl::Kernel kernel;
//        cl::CommandQueue queue;
//        cl::Buffer samplesBuffer;
//        cl_int samplesCount;
//    };
//}}
//
//#endif // __RAYTRACER_TRACERS_TRACER_HPP__
