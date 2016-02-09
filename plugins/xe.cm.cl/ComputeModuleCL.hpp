
#pragma once 

#ifndef __xe_cm_computemodulecl_hpp__
#define __xe_cm_computemodulecl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/cm/ComputeModule.hpp>

namespace xe { namespace cm {
    class ComputeModuleCL : public ComputeModule {
    public:
        ComputeModuleCL();
        
        ~ComputeModuleCL();
        
        virtual std::vector<const PlatformInfo*> enumeratePlatforms() const override;

        virtual PlatformPtr createPlatform(const PlatformInfo *info) override;

        virtual PlatformPtr createPlatform() override;

    private:
        std::vector<const PlatformInfo*> platforms;
    };
}}

#endif
