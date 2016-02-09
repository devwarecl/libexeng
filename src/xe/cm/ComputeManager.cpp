
#include "ComputeManager.hpp"

#include <cassert>
#include <map>
#include <xe/cm/ComputeModuleDesc.hpp>

namespace xe { namespace cm {
    
    typedef std::map<xe::cm::ComputeModuleDesc, xe::cm::ComputeModuleFactory*> FactoryMap;

    struct ComputeManager::Private {
        FactoryMap factories;
    };

    ComputeManager::ComputeManager() {
        this->impl = new ComputeManager::Private();        
    }

    ComputeManager::~ComputeManager() {
        delete this->impl;
    }
    
    ComputeModulePtr ComputeManager::createComputeModule() {
        assert(this->impl);
        
		ComputeModulePtr computeModule;

        for (auto pair : this->impl->factories) {
            computeModule = pair.second->create();
            break;
        }

		return computeModule;
    }
    
    ComputeModulePtr ComputeManager::createComputeModule(const ComputeModuleDesc &desc) {
        assert(this->impl);
        
        return this->impl->factories[desc]->create();
    }
    
    void ComputeManager::addFactory(ComputeModuleFactory *factory) {
        assert(this->impl);
        
        this->impl->factories[factory->getDesc()] = factory;
    }
    
    void ComputeManager::removeFactory(ComputeModuleFactory *factory) {
        assert(this->impl);
        
        this->impl->factories.erase(factory->getDesc());
    }
    
    std::vector<ComputeModuleDesc> ComputeManager::enumerate() const {
        assert(this->impl);
        
        std::vector<ComputeModuleDesc> descs;
        
        for (auto pair : this->impl->factories) {
            descs.push_back(pair.first);
        }
        
        return descs;
    }
}}
