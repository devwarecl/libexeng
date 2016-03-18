
#include "ComputeManager.hpp"

#include <cassert>
#include <map>
#include <xe/cm/ComputeModuleDesc.hpp>

namespace xe { namespace cm {
    
    typedef std::map<ComputeModuleDesc, ComputeModuleFactory*> FactoryMap;

    struct ComputeManager::Private {
        FactoryMap factories;
    };

    ComputeManager::ComputeManager() {
        impl = new ComputeManager::Private();        
    }

    ComputeManager::~ComputeManager() {
        delete impl;
    }
    
    ComputeModulePtr ComputeManager::createComputeModule() {
        assert(impl);
        
		ComputeModulePtr computeModule;
        
        assert(impl->factories.size() > 0);
        
        for (auto pair : impl->factories) {
            computeModule = pair.second->create();
            break;
        }

        assert(computeModule);

		return computeModule;
    }
    
    ComputeModulePtr ComputeManager::createComputeModule(const ComputeModuleDesc &desc) {
        assert(impl);
        
        return impl->factories[desc]->create();
    }
    
    void ComputeManager::addFactory(ComputeModuleFactory *factory) {
        assert(impl);
        
        impl->factories[factory->getDesc()] = factory;
    }
    
    void ComputeManager::removeFactory(ComputeModuleFactory *factory) {
        assert(impl);
        
        impl->factories.erase(factory->getDesc());
    }
    
    std::vector<ComputeModuleDesc> ComputeManager::enumerate() const {
        assert(impl);
        
        std::vector<ComputeModuleDesc> descs;
        
        for (auto pair : impl->factories) {
            descs.push_back(pair.first);
        }
        
        return descs;
    }
}}
