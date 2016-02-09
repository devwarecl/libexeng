
#include "DeviceCL.hpp"
#include "ContextCL.hpp"

namespace xe { namespace cm {
    
    DeviceCL::DeviceCL(cl::Platform &platform_, cl::Device &device_) 
        : platform(platform_), device(device_) {}
    
    DeviceCL::~DeviceCL() {}
    
    DeviceInfo DeviceCL::getInfo() {
        return {device.getInfo<CL_DEVICE_NAME>(), device.getInfo<CL_DEVICE_VENDOR>()};
    }
    
    ContextPtr DeviceCL::createContext() {
        ContextPtr context = std::make_unique<ContextCL>(device, nullptr);
        
        return context;
    }
}}
