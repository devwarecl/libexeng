
#pragma once 

#ifndef __xe_cm_computemodulecl_hpp__
#define __xe_cm_computemodulecl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/cm/ComputeModule.hpp>

#include "PlatformCL.hpp"

namespace xe { namespace cm {
    class ComputeModuleCL : public ComputeModule {
    public:
        ComputeModuleCL();
        
        ~ComputeModuleCL();
        
        virtual std::vector<Platform*> enumeratePlatforms() override;

    private:
        std::vector<PlatformCL> platforms;
    };
}}

#endif
