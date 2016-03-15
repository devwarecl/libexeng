
#pragma once

#ifndef __xe_cm_deviceinfo_hpp__
#define __xe_cm_deviceinfo_hpp__

#include <string>
#include <xe/Config.hpp>
#include <xe/Enum.hpp>

namespace xe { namespace cm {

	struct DeviceType : public Enum {
		enum Enum {
			CPU = 1,
			GPU = 2
		};
	};

    class EXENGAPI DeviceInfo {
	public:
        DeviceInfo();
        
        DeviceInfo(const std::string &name, const std::string &vendor, DeviceType::Enum type);

		~DeviceInfo();
        
        bool operator== (const DeviceInfo &info) const;
        bool operator!= (const DeviceInfo &info) const;

		std::string getName() const;

		std::string getVendor() const;

		DeviceType::Enum getType() const;

	private:
		struct Private;
		Private *impl = nullptr;
    };
}}

#endif
