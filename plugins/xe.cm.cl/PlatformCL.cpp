
#include "PlatformCL.hpp"
#include "DeviceCL.hpp"

namespace xe { namespace cm {
    PlatformCL::PlatformCL() {
    }

    PlatformCL::~PlatformCL() {
    }

    DevicePtr PlatformCL::createDevice() {
        return DevicePtr();
    }

    DevicePtr PlatformCL::createDevice(const DeviceInfo &info) {
        return DevicePtr();
    }
        
    std::vector<DeviceInfo> PlatformCL::enumerateDevices() const {
        std::vector<DeviceInfo> infos;

        return infos;
    }
}}
