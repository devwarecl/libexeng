
#pragma once

#ifndef __xe_cl_platformcl_hpp__
#define __xe_cl_platformcl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/cm/Platform.hpp>

namespace xe { namespace cm {

    class PlatformCL : public Platform {
    public:
        PlatformCL();

        ~PlatformCL();

        virtual DevicePtr createDevice() override;

        virtual DevicePtr createDevice(const DeviceInfo &info) override;
        
        virtual std::vector<DeviceInfo> enumerateDevices() const override;

    private:
        cl::Platform platform;
    };
}}

#endif
