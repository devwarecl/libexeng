
#pragma once

#ifndef __xe_cm_computemanager_hpp__
#define __xe_cm_computemanager_hpp__

#include <vector>
#include <xe/Config.hpp>
#include <xe/cm/ComputeModule.hpp>
#include <xe/cm/ComputeModuleFactory.hpp>
#include <xe/cm/ComputeLanguage.hpp>

namespace xe { namespace cm {
    class EXENGAPI ComputeManager {
    public:
        ComputeManager();
        virtual ~ComputeManager();
        
        ComputeModulePtr createComputeModule();
        ComputeModulePtr createComputeModule(const ComputeModuleDesc &desc);
        
        void addFactory(ComputeModuleFactory *factory);
        void removeFactory(ComputeModuleFactory *factory);
        
        std::vector<ComputeModuleDesc> enumerate() const;
        
    private:
        struct Private;
        Private *impl = nullptr;
    };
}}

#endif
