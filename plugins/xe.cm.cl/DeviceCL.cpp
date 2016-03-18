
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
        ContextPtr context = std::make_unique<ContextCL>(device, platform, nullptr);
        
        return context;
    }
    
    ContextPtr DeviceCL::createContext(xe::gfx::GraphicsDriver *driver) {
		assert(driver);
        
        ContextPtr context = std::make_unique<ContextCL>(device, platform, driver);
        
        return context;
    }
}}
