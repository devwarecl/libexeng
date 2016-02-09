
#pragma once

#ifndef __xe_cm_platforminfo_hpp__
#define __xe_cm_platforminfo_hpp__

#include <string>
#include <xe/Config.hpp>
#include <xe/Enum.hpp>
#include <xe/Object.hpp>

namespace xe { namespace cm {

    struct PlatformVendor : public Enum {
        enum Enum {
            Unknown,
            Intel,
            nVidia,
            AMD
        };
    };

    class EXENGAPI PlatformInfo : public Object {
    public:
        virtual ~PlatformInfo() {}

        virtual std::string getName() const = 0;

        virtual std::string getDesc() const = 0;

        virtual PlatformVendor::Enum getVendor() const = 0;
    };
}}

#endif
