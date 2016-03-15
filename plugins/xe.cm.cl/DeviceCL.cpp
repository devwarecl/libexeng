
#include "DeviceCL.hpp"
#include "ContextCL.hpp"

#include <xe/Exception.hpp>
#include <xe/gfx/GraphicsDriver.hpp>

#if defined (EXENG_WINDOWS)      
  #include <Windows.h>
            
#elif defined (EXENG_UNIX)
  #include <GL/glx.h>
  
#elif defined (EXENG_MACOS)
  #error Unsupported platform
#endif

namespace xe { namespace cm {
    
    DeviceCL::DeviceCL(const cl::Platform &platform_, const cl::Device &device_) {
        this->platform = platform_;
        this->device = device_;
    }
    
    DeviceCL::~DeviceCL() {}
    
    DeviceInfo DeviceCL::getInfo() {
		auto deviceTypeCL = device.getInfo<CL_DEVICE_TYPE>();

		DeviceType::Enum deviceType;

		switch (deviceTypeCL) {
			case CL_DEVICE_TYPE_CPU: deviceType = DeviceType::CPU; break;
			case CL_DEVICE_TYPE_GPU: deviceType = DeviceType::GPU; break;
		}

        return {device.getInfo<CL_DEVICE_NAME>(), device.getInfo<CL_DEVICE_VENDOR>(), deviceType};
    }
    
    ContextPtr DeviceCL::createContext() {
        cl_context_properties properties[] = {
            CL_CONTEXT_PLATFORM, (cl_context_properties)platform(),
            0, 0
        };
        
        ContextPtr context = std::make_unique<ContextCL>(device, properties);
        
        return context;
    }
    
    ContextPtr DeviceCL::createContext(xe::gfx::GraphicsDriver *driver) {
        std::vector<cl_context_properties> properties = {
            CL_CONTEXT_PLATFORM, (cl_context_properties)platform()
        };
        
        if (driver->getBackend() == xe::gfx::GraphicsBackend::OpenGL_Core) {
            // We should first check for cl_khr_gl_sharing extension.
#if defined (EXENG_WINDOWS)
            properties.push_back(CL_GL_CONTEXT_KHR);
            properties.push_back((cl_context_properties)wglGetCurrentContext());
            
            properties.push_back(CL_WGL_HDC_KHR);
            properties.push_back((cl_context_properties)wglGetCurrentDC());
            
#elif defined (EXENG_UNIX)
            properties.push_back(CL_GL_CONTEXT_KHR);
            properties.push_back((cl_context_properties)glXGetCurrentContext());
            
            properties.push_back(CL_GLX_DISPLAY_KHR);
            properties.push_back((cl_context_properties)glXGetCurrentDisplay());
            
#elif defined (EXENG_MACOS)
            properties.push_back(CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE);
            properties.push_back(cl_context_properties)CGLGetShareGroup(CGLGetCurrentContext());
#endif
        } else {
            EXENG_THROW_EXCEPTION("DeviceCL::createContext: Unsupported graphics backend.");
        }
        
        properties.push_back(0);
        
        ContextPtr context = std::make_unique<ContextCL>(device, properties.data());
        
        return context;
    }
}}
