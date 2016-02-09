
#include "DeviceCL.hpp"
#include "ContextCL.hpp"

namespace xe { namespace cm {
    
    DeviceCL::DeviceCL(cl::Platform &platform_, cl::Device &device_) 
    : platform(platform_), device(device_) {
    }
    
    DeviceCL::~DeviceCL() {}
    
    DeviceInfo DeviceCL::getInfo() {
        return {"OpenCL", "Vendor"};
    }
    
    ContextPtr DeviceCL::createContext() {
        return ContextPtr();
    }
}}
