
#include "ComputeModuleCL.hpp"
#include "PlatformInfoCL.hpp"

namespace xe { namespace cm {
    ComputeModuleCL::ComputeModuleCL() {
        std::vector<cl::Platform> cl_platforms;
        cl::Platform::get(&cl_platforms);
        
        for (cl::Platform &platform : cl_platforms) {
            platforms.push_back(PlatformCL(platform));
        }
    }
    
    ComputeModuleCL::~ComputeModuleCL() {}
    
    std::vector<Platform*> ComputeModuleCL::enumeratePlatforms() {
        std::vector<Platform*> result;
        
        for (PlatformCL &platform : platforms) {
            result.push_back(&platform);
        }
        
        return result;
    }
}}
