
#include "PlatformCL.hpp"
#include "DeviceCL.hpp"

namespace xe { namespace cm {
    PlatformCL::PlatformCL(cl::Platform &platform) {
        this->platform = platform;
        
        std::vector<cl::Device> devices;
        
        this->platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
        
        for (cl::Device& device : devices) {
            this->devices.push_back(DeviceCL(platform, device));
        }
    }

    PlatformCL::~PlatformCL() {}
   
    std::vector<Device*> PlatformCL::enumerateDevices() {
        std::vector<Device*> result;
        
        for (DeviceCL device : devices) {
            result.push_back(&device);
        }
        
        return result;
    }
}}
