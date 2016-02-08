
#pragma once

#ifndef __xe_cm_devicecl_hpp__
#define __xe_cm_devicecl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/cm/Device.hpp>

namespace xe { namespace cm {

    class DeviceCL : public Device {
    public:
        DeviceCL(cl::Platform &platform);
        
        ~DeviceCL();
        
        virtual DeviceInfo getInfo() override;
        
        virtual ContextPtr createContext() override;

        cl::Device& getWrapped() {
            return device;
        }
        
        const cl::Device& getWrapped() const {
            return device;
        }
        
    private:
        cl::Platform &platform;
        cl::Device device;
    };    
}}

#endif 
