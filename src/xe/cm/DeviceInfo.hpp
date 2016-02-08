
#pragma once

#ifndef __xe_cm_deviceinfo_hpp__
#define __xe_cm_deviceinfo_hpp__

#include <string>
#include <xe/Config.hpp>

namespace xe { namespace cm {

    struct EXENGAPI DeviceInfo {
        std::string name;
        std::string vendor;
        
        DeviceInfo();
        
        DeviceInfo(const std::string &name, const std::string &vendor);
        
        bool operator== (const DeviceInfo &info) const;
        bool operator!= (const DeviceInfo &info) const;
    };
}}

#endif
