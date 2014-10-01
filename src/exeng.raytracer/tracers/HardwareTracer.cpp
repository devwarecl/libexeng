/**
 * @file HardwareTracer.hpp
 * @brief Interfaz del objeto trazador de rayos
 */

// #define __CL_ENABLE_EXCEPTIONS
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS 

#include <fstream>

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
        cl::Buffer samplesBuffer;
        cl_int samplesCount;
    };
    
    std::string getRootPath() {
        return std::string(RAYTRACER_ROOT_FOLDER);
    }

    std::string loadFile(const std::string &file) {
        std::ifstream fs;
        fs.open(file.c_str(), std::ios_base::in);

        if (!fs.is_open()) {
            throw std::runtime_error("loadFile: File '" + file + "' couldn't be loaded.");
        }

        std::string content;
        std::string line;

        while (!fs.eof()) {
            std::getline(fs, line);
            content += line + "\n";
        }

        return content;
    }
    
    cl::Buffer createCLBuffer(cl::Context &context, exeng::Buffer *in) {
        if (in == nullptr) {
            throw std::runtime_error("[HardwareTracer.cpp] createCLBuffer -> The input buffer can't be a nullptr.");
        }
        
        cl_int errCode = 0;
        
        cl::Buffer result /*= cl::Buffer(context, , in->getSize(), in->getDataPtr())*/;
        
        return result;
    }
    
    HardwareTracer::HardwareTracer(const Scene *scene, const raytracer::samplers::Sampler *sampler) : Tracer(scene, nullptr), impl(new HardwareTracer::Private())  {
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
        
        // initialize the OpenCL context
        cl::Context context = cl::Context({device}, properties);
        
        // pass the samples to OpenCL
        size_t bufferSize = sizeof(Vector2f) * sampler->getSampleCount();
        cl_mem_flags bufferFlags = CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR;
        void* bufferData = (void*)(sampler->getSampleData());

        cl::Buffer samplesBuffer = cl::Buffer(context, bufferFlags, bufferSize, bufferData);

        // Create a Program object
        std::string programSource = loadFile(getRootPath() + "kernels/TraceRay.cl");

        cl::Program::Sources programSources;
        programSources.push_back({programSource.c_str(), programSource.size()});
        
        // Compile 
        cl::Program program = cl::Program(context, programSources);
        program.build({device}, "-Werror");
        if (program.build({device}) != CL_SUCCESS) {
            std::string msg;
            msg += "OpenCL program compile error: ";
            msg += program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
            msg += "\n";
            
            throw std::runtime_error(msg);
        }
        
        cl::Kernel kernel = cl::Kernel(program, "tracerKernel");
        
        // Command queue
        cl::CommandQueue queue = cl::CommandQueue(context, device);
        
        // Save the final variables
        this->impl->platform = platform;
        this->impl->device = device;
        this->impl->context = context;
        this->impl->program = program;
        this->impl->kernel = kernel;
        this->impl->queue = queue;
        this->impl->samplesBuffer = samplesBuffer;
        this->impl->samplesCount = sampler->getSampleCount();
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
            str += "HardwareTracer::setRenderTarget: Invalid render target texture. Error code: ";
            str += boost::lexical_cast<std::string>(errorCode);
            
            throw std::runtime_error(str);
        }
        
        this->impl->image = image;
        Tracer::setRenderTarget(renderTarget);
    }
    
    HardwareTracer::~HardwareTracer() {}

    void HardwareTracer::render(const exeng::scenegraph::Camera *camera) {
        Vector3i size = this->getRenderTarget()->geSize();
        cl::Image2DGL &image = this->impl->image;
        cl::Buffer &samplesBuffer = this->impl->samplesBuffer;
        cl::CommandQueue &queue = this->impl->queue;
        cl::Event event;
        cl_int errCode = 0;
        
        cl_float cx, cy, cz;
        cl_float lx, ly, lz;
        cl_float ux, uy, uz;
        
        cx = camera->getPosition().x;
        cy = camera->getPosition().y;
        cz = camera->getPosition().z;
        
        lx = camera->getLookAt().x;
        ly = camera->getLookAt().y;
        lz = camera->getLookAt().z;
        
        ux = camera->getUp().x;
        uy = camera->getUp().y;
        uz = camera->getUp().z;
        
        this->impl->kernel.setArg(0, image);
        this->impl->kernel.setArg(1, samplesBuffer);
        this->impl->kernel.setArg(2, 16);
        this->impl->kernel.setArg(3, cx);
        this->impl->kernel.setArg(4, cy);
        this->impl->kernel.setArg(5, cz);
        this->impl->kernel.setArg(6, lx);
        this->impl->kernel.setArg(7, ly);
        this->impl->kernel.setArg(8, lz);
        this->impl->kernel.setArg(9, ux);
        this->impl->kernel.setArg(10, uy);
        this->impl->kernel.setArg(11, uz);
        
        std::vector<cl::Memory> buffersGL = {image};
        
        errCode = queue.enqueueAcquireGLObjects(&buffersGL, nullptr, &event);
        if (errCode != CL_SUCCESS) {
            std::cout << "Error Code:" << errCode << std::endl;
            throw std::runtime_error("HardwareTracer::render: OpenCL enqueueAcquire error.");
        }
        event.wait();
        
        errCode = queue.enqueueNDRangeKernel(this->impl->kernel, cl::NullRange, cl::NDRange(size.x, size.y), cl::NDRange(16, 16), nullptr, &event);
        if (errCode != CL_SUCCESS) {
            std::cout << "Error Code:" << errCode << std::endl;
            throw std::runtime_error("HardwareTracer::render: OpenCL enqueueNDRange error.");
        }
        event.wait();

        errCode = queue.enqueueReleaseGLObjects(&buffersGL, nullptr, &event);
        if (errCode != CL_SUCCESS) {
            std::cout << "Error Code:" << errCode << std::endl;
            throw std::runtime_error("HardwareTracer::render: OpenCL enqueueRelease error.");
        }
        event.wait();

        errCode = queue.finish();
        if (errCode != CL_SUCCESS) {
            std::cout << "Error Code:" << errCode << std::endl;
            throw std::runtime_error("HardwareTracer::render: OpenCL queueFinish error.");
        }
    }
}}
