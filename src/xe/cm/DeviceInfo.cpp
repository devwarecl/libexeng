
#include "DeviceInfo.hpp"

namespace xe { namespace cm {

	struct DeviceInfo::Private {
		std::string name;
        std::string vendor;        
	};

    DeviceInfo::DeviceInfo() {
		impl = new DeviceInfo::Private();
	}
    
    DeviceInfo::DeviceInfo(const std::string &name, const std::string &vendor) {
		impl = new DeviceInfo::Private();

		impl->name = name;
		impl->vendor = vendor;
	}
    
	DeviceInfo::~DeviceInfo() {
		delete impl;
	}

    bool DeviceInfo::operator== (const DeviceInfo &other) const {
        if (this->getName() != other.getName()) {
            return false;
        }
        
        if (this->getVendor() != other.getVendor()) {
            return false;
        }
        
        return true;
    }
    
    bool DeviceInfo::operator!= (const DeviceInfo &other) const {
        return !(*this == other);
    }
	
	std::string DeviceInfo::getName() const {
		return impl->name;
	}

	std::string DeviceInfo::getVendor() const {
		return impl->vendor;
	}
}}
