
#include "ComputeModuleFactoryCL.hpp"
#include "ComputeModuleCL.hpp"

namespace xe { namespace cm {
    
    ComputeModuleFactoryCL::~ComputeModuleFactoryCL() {
    
    }
    
    ComputeModulePtr ComputeModuleFactoryCL::create() {
        
        ComputeModulePtr module;
        
        module = std::make_unique<ComputeModuleCL>();
        
        return module;
    }
            
    ComputeModuleDesc ComputeModuleFactoryCL::getDesc() {
        ComputeModuleDesc desc;
    
        desc.language = ComputeLanguage::OpenCL;
    
        return desc;    
    }
}}

