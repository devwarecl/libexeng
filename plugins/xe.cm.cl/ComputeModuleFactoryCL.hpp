
#pragma once 

#ifndef __xe_cm_computemodulefactorycl_hpp__
#define __xe_cm_computemodulefactorycl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/cm/ComputeModuleFactory.hpp>

#include "ComputeModuleCL.hpp"

namespace xe { namespace cm {
    class ComputeModuleFactoryCL : public ComputeModuleFactory {
    public:        
        virtual ~ComputeModuleFactoryCL();
        
        virtual ComputeModulePtr create() override;
                
        virtual ComputeModuleDesc getDesc() override;
    };
}}

#endif
