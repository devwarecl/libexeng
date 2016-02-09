
#include "PlatformInfoCL.hpp"

namespace xe { namespace cm {

    PlatformInfoCL::~PlatformInfoCL() {}

    std::string PlatformInfoCL::getName() const {
        return "";
    }

    std::string PlatformInfoCL::getDesc() const {
        return "";
    }

    PlatformVendor::Enum PlatformInfoCL::getVendor() const {
        return PlatformVendor::Unknown;
    }
}}