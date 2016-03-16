
#include "DeviceInfo.hpp"

#include <cassert>

namespace xe { namespace cm {

	struct DeviceInfo::Private {
		std::string name;
        std::string vendor;        
		DeviceType::Enum type;
	};

    DeviceInfo::DeviceInfo() {
		impl = new DeviceInfo::Private();
	}
    
    DeviceInfo::DeviceInfo(const std::string &name, const std::string &vendor, DeviceType::Enum type) {
		impl = new DeviceInfo::Private();

		impl->name = name;
		impl->vendor = vendor;
		impl->type = type;
	}
    
	DeviceInfo::~DeviceInfo() {
		delete impl;
	}

    bool DeviceInfo::operator== (const DeviceInfo &other) const {
		assert(impl);

        if (this->getName() != other.getName()) {
            return false;
        }
        
        if (this->getVendor() != other.getVendor()) {
            return false;
        }

		if (this->getType() != other.getType()) {
            return false;
        }
        
        return true;
    }
    
    bool DeviceInfo::operator!= (const DeviceInfo &other) const {
		assert(impl);

        return !(*this == other);
    }
	
	std::string DeviceInfo::getName() const {
		assert(impl);

		return impl->name;
	}

	std::string DeviceInfo::getVendor() const {
		assert(impl);

		return impl->vendor;
	}

	DeviceType::Enum DeviceInfo::getType() const {
		assert(impl);

		return impl->type;
	}
}}
