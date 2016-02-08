
#pragma once

#ifndef __xe_cm_deviceinfo_hpp__
#define __xe_cm_deviceinfo_hpp__

#include <string>
#include <xe/Config.hpp>

namespace xe { namespace cm {

    class EXENGAPI DeviceInfo {
	public:
        DeviceInfo();
        
        DeviceInfo(const std::string &name, const std::string &vendor);

		~DeviceInfo();
        
        bool operator== (const DeviceInfo &info) const;
        bool operator!= (const DeviceInfo &info) const;

		std::string getName() const;

		std::string getVendor() const;

	private:
		struct Private;
		Private *impl = nullptr;
    };
}}

#endif
