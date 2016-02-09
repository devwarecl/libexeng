
#pragma once

#ifndef __xe_cm_computemodule_hpp__
#define __xe_cm_computemodule_hpp__

#include <memory>

#include <vector>
#include <xe/Config.hpp>
#include <xe/cm/Platform.hpp>
#include <xe/cm/PlatformInfo.hpp>

namespace xe { namespace cm {    
    class EXENGAPI ComputeModule {
    public:
        virtual ~ComputeModule();

        virtual std::vector<Platform*> enumeratePlatforms() = 0;
    };
    
    typedef std::unique_ptr<ComputeModule> ComputeModulePtr;
}}

#endif
