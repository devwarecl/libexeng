
#include "ComputeModuleCL.hpp"
#include "PlatformInfoCL.hpp"

namespace xe { namespace cm {
    ComputeModuleCL::ComputeModuleCL() {
        std::vector<const PlatformInfo*> platforms;

        std::vector<cl::Platform> cl_platforms;

        cl::Platform::get(&cl_platforms);
    }
        
    ComputeModuleCL::~ComputeModuleCL() {}
        
    std::vector<const PlatformInfo*> ComputeModuleCL::enumeratePlatforms() const {
        return platforms;
    }

    PlatformPtr ComputeModuleCL::createPlatform(const PlatformInfo *info) {
        return PlatformPtr();
    }

    PlatformPtr ComputeModuleCL::createPlatform() {
        return PlatformPtr();
    }
}}
