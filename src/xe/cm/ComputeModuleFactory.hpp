
#pragma once

#ifndef __xe_cm_computemodulefactory_hpp__
#define __xe_cm_computemodulefactory_hpp__

#include <xe/Config.hpp>
#include <xe/cm/ComputeModule.hpp>
#include <xe/cm/ComputeModuleDesc.hpp>

namespace xe { namespace cm {
    class EXENGAPI ComputeModuleFactory {
    public:
        virtual ~ComputeModuleFactory();
        
        virtual ComputeModulePtr create() = 0;
                
        virtual ComputeModuleDesc getDesc() = 0;
    };
}}

#endif 
