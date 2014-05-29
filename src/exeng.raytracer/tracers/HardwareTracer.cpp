/**
 * @file HardwareTracer.hpp
 * @brief Interfaz del objeto trazador de rayos
 */

#include "HardwareTracer.hpp"

#include <CL/cl.hpp>
#include <GLFW/glfw3.h>
#include <GL/glx.h>

using namespace exeng;
using namespace exeng::graphics;
using namespace exeng::scenegraph;

namespace raytracer { namespace tracers {
    
    struct HardwareTracer::Private {
        cl::Platform platform;
        cl::Device device;
        cl::Context context;
        cl::Program program;
        cl::Image2DGL image2D;
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
        GLuint textureId = renderTarget->getHandle();
        if (textureId <= 0) {
            throw std::runtime_error("Invalid render target texture id (non positive)");
        }
        
        cl::Image2DGL image2D(this->impl->context, CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, textureId);
        this->impl->image2D = image2D;
        
        Tracer::setRenderTarget(renderTarget);
    }
    
    HardwareTracer::~HardwareTracer() {}
    
    void HardwareTracer::render(const exeng::scenegraph::Camera *camera) {
        auto size = this->getRenderTarget()->getSize();
        
        cl::Image2DGL &image2D = this->impl->image2D;
        
        cl::KernelFunctor tracerKernel( 
            cl::Kernel(this->impl->program, "tracerKernel"),
            this->impl->queue,
            cl::NullRange,
            cl::NDRange(size.x, size.y),
            cl::NullRange
        );
        
        tracerKernel(image2D);
    }
}}
