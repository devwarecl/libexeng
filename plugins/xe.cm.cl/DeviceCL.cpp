
#include "DeviceCL.hpp"
#include "ContextCL.hpp"

namespace xe { namespace cm {
    
    DeviceCL::DeviceCL(const cl::Platform &platform_, const cl::Device &device_) {
        this->platform = platform_;
        this->device = device_;
    }
    
    DeviceCL::~DeviceCL() {}
    
    DeviceInfo DeviceCL::getInfo() {
        return {device.getInfo<CL_DEVICE_NAME>(), device.getInfo<CL_DEVICE_VENDOR>()};
    }
    
    ContextPtr DeviceCL::createContext() {
        cl_context_properties properties[] = {
            CL_CONTEXT_PLATFORM, (cl_context_properties)platform(),
            0, 0
        };
        
        ContextPtr context = std::make_unique<ContextCL>(device, properties);
        
        return context;
    }
}}
