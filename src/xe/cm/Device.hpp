
#pragma once

#ifndef __xe_cm_device_hpp__
#define __xe_cm_device_hpp__

#include <memory>
#include <xe/Object.hpp>
#include <xe/cm/Context.hpp>
#include <xe/cm/DeviceInfo.hpp>
#include <xe/gfx/Forward.hpp>

namespace xe { namespace cm {

    class EXENGAPI Device : public Object {
    public:
        virtual ~Device();
      
        virtual DeviceInfo getInfo() = 0;
        
        virtual ContextPtr createContext() = 0;
        
        virtual ContextPtr createContext(xe::gfx::GraphicsDriver *driver) = 0;
    };

    typedef std::unique_ptr<Device> DevicePtr;
}}

#endif
