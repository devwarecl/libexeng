
#pragma once

#ifndef __xe_cl_platformcl_hpp__
#define __xe_cl_platformcl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/cm/Platform.hpp>

#include "DeviceCL.hpp"

namespace xe { namespace cm {

    class PlatformCL : public Platform {
    public:
        explicit PlatformCL(const cl::Platform &platform);

        ~PlatformCL();

        virtual std::vector<Device*> enumerateDevices() override;

    private:
        cl::Platform platform;
        std::vector<DeviceCL> devices;        
    };
}}

#endif
