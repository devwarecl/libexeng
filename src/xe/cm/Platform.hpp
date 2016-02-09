#pragma once

#ifndef __xe_cm_platform_hpp__
#define __xe_cm_platform_hpp__

#include <memory>
#include <vector>
#include <xe/Config.hpp>
#include <xe/cm/Device.hpp>

namespace xe { namespace cm {
    class EXENGAPI Platform {
    public:
        virtual ~Platform() {}
                
        virtual DevicePtr createDevice() = 0;

        virtual DevicePtr createDevice(const DeviceInfo &info) = 0;
        
        virtual std::vector<DeviceInfo> enumerateDevices() const = 0;
    };

    typedef std::unique_ptr<Platform> PlatformPtr;
}}

#endif
