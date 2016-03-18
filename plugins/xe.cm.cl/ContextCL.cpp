
#include "ContextCL.hpp"

#include "BufferCL.hpp"
#include "BufferCL_GL.hpp"
#include "DeviceCL.hpp"
#include "KernelCL.hpp"
#include "PluginCL.hpp"
#include "ProgramCL.hpp"
#include "ProgramModuleCL.hpp"
#include "QueueCL.hpp"
#include "ImageCL.hpp"

#include <vector>

namespace xe { namespace cm {
    
    ContextCL::ContextCL(const cl::Device &device_, const cl::Platform &platform, xe::gfx::GraphicsDriver *graphicsDriver_) {
        
        std::vector<cl_context_properties> properties = {
            CL_CONTEXT_PLATFORM, (cl_context_properties)platform()
        };
        
        if (graphicsDriver_) {
            assert(graphicsDriver_->getBackend() == xe::gfx::GraphicsBackend::OpenGL_Core);
            
            auto backend = graphicsDriver_->getOpenGLBackend();
            
            assert(backend);
            
            const std::string extensions = device_.getInfo<CL_DEVICE_EXTENSIONS>();
            const std::int32_t position = extensions.find("cl_khr_gl_sharing");
            const bool found = position != std::string::npos;
            
            std::cout << "OpenCL extensions: " << std::endl;
            std::cout << extensions << std::endl;
            
            if (!found) {
                std::cerr << "The extension 'cl_khr_gl_sharing' wasn't found. I will continue anyway." << std::endl;
            }
            
            // We should check first for the cl_khr_gl_sharing extension.
#if defined (EXENG_WINDOWS)
            properties.push_back(CL_GL_CONTEXT_KHR);
            properties.push_back((cl_context_properties)wglGetCurrentContext());
            
            properties.push_back(CL_WGL_HDC_KHR);
            properties.push_back((cl_context_properties)wglGetCurrentDC());
            
#elif defined (EXENG_UNIX)
            properties.push_back(CL_GL_CONTEXT_KHR);
            properties.push_back((cl_context_properties)backend->getGLContext());
            
            properties.push_back(CL_GLX_DISPLAY_KHR);
            properties.push_back((cl_context_properties)backend->getOSContext());
            
#elif defined (EXENG_MACOS)
            properties.push_back(CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE);
            properties.push_back(cl_context_properties)CGLGetShareGroup(CGLGetCurrentContext());
#endif
        }
        
        properties.push_back(0);
    
        device = device_;
        graphicsDriver = graphicsDriver_;
        context = cl::Context(device, properties.data());
    }
    
    ContextCL::~ContextCL() {}
    
    ComputeLanguage::Enum ContextCL::getLanguage() const {
        return ComputeLanguage::OpenCL;
    }
    
    BufferPtr ContextCL::createBuffer(Queue *queue, const int size, const void *data) {
        BufferPtr buffer = std::make_unique<BufferCL> (
            &static_cast<QueueCL*>(queue)->getWrapped(),
            context,
            size
        );
        
        if (data) {
            auto locker = buffer->getLocker(BufferUsage::Write);
            std::memcpy(locker.getPointer(), data, locker.getSize());
        }
        
        return buffer;
    }
    
    BufferPtr ContextCL::createBuffer(Buffer *graphicsBuffer) {
        assert(graphicsBuffer);
        assert(graphicsDriver);
        
        cl_GLuint bufferId = graphicsBuffer->getHandle();
        
        BufferPtr buffer = std::make_unique<BufferCL_GL>(context, bufferId);
        
        return buffer;
    }
    
    ProgramModulePtr ContextCL::createProgramModule(const std::string &source) {
        ProgramModulePtr module = std::make_unique<ProgramModuleCL>(source);
        
        return module;
    }
    
    ProgramPtr ContextCL::createProgram() {
        ProgramPtr program = std::make_unique<ProgramCL>(context, device);
        
        return program;
    }
    
    KernelPtr ContextCL::createKernel(const Program* program, const std::string &kernel_name) {
        KernelPtr kernel = std::make_unique<KernelCL> (
            graphicsDriver,
            context,
            static_cast<const ProgramCL*>(program)->getWrapped(),
            kernel_name
        );
        
        return kernel;
    }
    
    QueuePtr ContextCL::createQueue() {
        QueuePtr queue = std::make_unique<QueueCL>(context);
        
        return queue;
    }
    
    xe::gfx::ImagePtr ContextCL::createImage(gfx::Texture *texture) {
        assert(texture);
        
        cl_GLuint textureId = texture->getHandle();
        
        xe::gfx::ImagePtr image = std::make_unique<ImageCL>(context, textureId);
        
        return image;
    }
}}
