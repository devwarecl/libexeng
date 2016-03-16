
#include "PlatformCL.hpp"
#include "DeviceCL.hpp"

namespace xe { namespace cm {
    PlatformCL::PlatformCL(const cl::Platform &platform_) {
        platform = platform_;
        
        std::vector<cl::Device> devicescl;
        platform.getDevices(CL_DEVICE_TYPE_GPU, &devicescl);
        
        for (cl::Device& devicecl : devicescl) {
            devices.push_back(DeviceCL(platform, devicecl));
        }
    }

    PlatformCL::~PlatformCL() {}
   
    std::vector<Device*> PlatformCL::enumerateDevices() {
        std::vector<Device*> result;
        
        for (DeviceCL &device : devices) {
            result.push_back(&device);
        }
        
        return result;
    }
}}
