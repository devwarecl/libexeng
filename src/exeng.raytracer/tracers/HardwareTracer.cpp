/**
 * @file HardwareTracer.hpp
 * @brief Interfaz del objeto trazador de rayos
 */

#define __CL_ENABLE_EXCEPTIONS
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS 

#include "HardwareTracer.hpp"

#include <boost/lexical_cast.hpp>
#include <CL/cl.h>
#include <CL/cl_gl.h>

#undef CL_VERSION_1_2
#include <CL/cl.hpp>
#include <GLFW/glfw3.h>

#if defined (EXENG_UNIX)
  #include <GL/glx.h>
#endif

using namespace exeng;
using namespace exeng::math;
using namespace exeng::graphics;
using namespace exeng::scenegraph;

namespace raytracer { namespace tracers {
    
    struct HardwareTracer::Private {
        cl::Platform platform;
        cl::Device device;
        cl::Context context;
        cl::Program program;
        cl::Image2DGL image;
        cl::Kernel kernel;
        cl::CommandQueue queue;
    };
    
    HardwareTracer::HardwareTracer(const Scene *scene ) : Tracer(scene, nullptr), impl(new HardwareTracer::Private())  {
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        
        if (platforms.size() == 0) {
            throw std::runtime_error("HardwareTracer::HardwareTracer: No OpenCL platforms available");
        }
        
        // Select the first platform
        cl::Platform platform = platforms[0];
        
        // Select the first GPU device of the first platform.
        std::vector<cl::Device> devices;
        platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
        if (devices.size() == 0) {
            throw std::runtime_error("HardwareTracer::HardwareTracer: No OpenCL GPU devices available");
        }
        
        cl::Device device = devices[0];
        
        // Set context properties for GL/CL interop.
        cl_context_properties properties[] = {
            // We need to add information about the OpenGL context with
            // which we want to exchange information with the OpenCL context.
#if defined (WIN32)
            // We should first check for cl_khr_gl_sharing extension.
            CL_GL_CONTEXT_KHR , (cl_context_properties) wglGetCurrentContext() ,
            CL_WGL_HDC_KHR , (cl_context_properties) wglGetCurrentDC() ,
#elif defined (__linux__)
            // We should first check for cl_khr_gl_sharing extension.
            CL_GL_CONTEXT_KHR , (cl_context_properties) glXGetCurrentContext() ,
            CL_GLX_DISPLAY_KHR , (cl_context_properties) glXGetCurrentDisplay() ,
#elif defined (__APPLE__)
            CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE , (cl_context_properties) CGLGetShareGroup( CGLGetCurrentContext() ) ,
#endif
            CL_CONTEXT_PLATFORM , (cl_context_properties) platform(),
            0 , 0 ,  
        };
        
        cl::Context context({device}, properties);
        
        // Create a Program object
        std::string programSource = "";
        programSource += "__kernel void tracerKernel(__write_only image2d_t bmp) { ";
        programSource += "  int2 coords = (int2)(get_global_id(0), get_global_id(1)); ";
        programSource += "  float4 color = (float4)(0.0f, 0.0f, 1.0f, 1.0f); ";
        programSource += "  write_imagef(bmp, coords, color); ";
        programSource += "}";
        
        cl::Program::Sources programSources;
        programSources.push_back({programSource.c_str(), programSource.size()});
        
        // Compile 
        cl::Program program(context, programSources);
        program.build({device});
        if (program.build({device}) != CL_SUCCESS) {
            std::string msg("");
            msg += "Error al compilar un programa OpenCL: ";
            msg += program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
            msg += "\n";
            
            throw std::runtime_error(msg);
        }
        
        cl::Kernel kernel(program, "tracerKernel");
        
        // Command queue
        cl::CommandQueue queue(context, device);
        
        // Save the final variables
        this->impl->platform = platform;
        this->impl->device = device;
        this->impl->context = context;
        this->impl->program = program;
        this->impl->kernel = kernel;
        this->impl->queue = queue;
    }
    
    void HardwareTracer::setRenderTarget(exeng::graphics::Texture *renderTarget) {
        // Create a OpenCL 2D image  from the render target Texture
        GLuint textureId = static_cast<GLuint>(renderTarget->getHandle());
        if (textureId <= 0) {
            throw std::runtime_error("Invalid render target texture id (non positive)");
        }
        
        cl_int errorCode = 0;
        
        cl::Image2DGL image(this->impl->context, CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, textureId, &errorCode);
        if (errorCode != CL_SUCCESS) {
            std::string str;
            str += "Invalid render target texture. Error code: ";
            str += boost::lexical_cast<std::string>(errorCode);
            
            throw std::runtime_error(str);
        }
        
        this->impl->image = image;
        Tracer::setRenderTarget(renderTarget);
    }
    
    HardwareTracer::~HardwareTracer() {}
    
    void HardwareTracer::render(const exeng::scenegraph::Camera *camera) {
        Vector3i size = this->getRenderTarget()->getSize();
        cl::Image2DGL &image = this->impl->image;
        cl::CommandQueue &queue = this->impl->queue;
        
        cl::size_t<3> origin;
        origin[0] = 0;
        origin[1] = 0;
        origin[2] = 0;
        
        cl::size_t<3> region;
        region[0] = size.x;
        region[1] = size.y;
        region[2] = 1;
        
        // The C++ OpenCL wrapper pass this param as 'void*' instead.
        void* ptr = const_cast<void*>(this->getRenderTarget()->getDataPtr());
        if (queue.enqueueWriteImage(image, CL_TRUE, origin, region, 0, 0, ptr) != CL_SUCCESS) {
            throw std::runtime_error("HardwareTracer::render: Error at writing the image buffer to the execution queue.");
        }
        
        // cl::KernelFunctor tracerKernel(this->impl->program, "tracerKernel");
    }
}}
