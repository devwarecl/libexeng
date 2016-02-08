
#include "DeviceCL.hpp"
#include "ContextCL.hpp"

namespace xe { namespace cm {
    
    DeviceCL::DeviceCL(cl::Platform &platform_) : platform(platform_) {
        
    }
    
    DeviceCL::~DeviceCL() {
        
    }
    
    DeviceInfo DeviceCL::getInfo() {
        return {"OpenCL", "Vendor"};
    }
    
    ContextPtr DeviceCL::createContext() {
        return ContextPtr();
    }
}}
