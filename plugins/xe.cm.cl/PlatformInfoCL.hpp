
#pragma once

#ifndef __xe_cm_platforminfocl_hpp__
#define __xe_cm_platforminfocl_hpp__

#include <xe/cm/PlatformInfo.hpp>

namespace xe { namespace cm {

    class PlatformInfoCL : public PlatformInfo {
    public:
        virtual ~PlatformInfoCL();

        virtual std::string getName() const;

        virtual std::string getDesc() const;

        virtual PlatformVendor::Enum getVendor() const;
    };

}}

#endif
