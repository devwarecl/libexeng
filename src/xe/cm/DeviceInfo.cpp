
#include "DeviceInfo.hpp"

namespace xe { namespace cm {

    DeviceInfo::DeviceInfo() {}
    
    DeviceInfo::DeviceInfo(const std::string &name_, const std::string &vendor_) : 
        name(name_), vendor(vendor_) {}
    
    bool DeviceInfo::operator== (const DeviceInfo &other) const {
        if (name != other.name) {
            return false;
        }
        
        if (vendor != other.vendor) {
            return false;
        }
        
        return true;
    }
    
    bool DeviceInfo::operator!= (const DeviceInfo &other) const {
        return ! (*this == other);
    }
}}
