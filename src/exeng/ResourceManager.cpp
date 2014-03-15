/**
 * @file ResourceManager.cpp
 * @brief Implement the resource factory methods
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <map>
#include <list>
#include <cassert>
#include <iostream>
#include <exeng/Resource.hpp>
#include <exeng/ResourceManager.hpp>

namespace exeng {
    
    struct ResourceManager::Private {
        //! Unnamed resources
        std::list<Resource*> resources;
        
        //! Named resources
        std::map<std::string, Resource*> namedResources;
    };
    
    
    ResourceManager::ResourceManager() : impl(nullptr) {
        this->impl = new ResourceManager::Private();
    }
    
    
    ResourceManager::~ResourceManager() {
        if (!this->impl) {
            return;
        }
        
#if defined (EXENG_DEBUG)
        std::cout << "ResourceManager::~ResourceManager: Releasing ";
        std::cout << this->impl->resources.size() << " objects:" << std::endl;
#endif
        
        for (Resource *resource : this->impl->resources) {
            assert(resource->resourceManager == this);
#if defined (EXENG_DEBUG)
            std::cout << "    " << resource->toString() << std::endl;
#endif
            resource->resourceManager = nullptr;
            resource->release();
        }
        
        this->impl->resources.clear();
        
#if defined (EXENG_DEBUG)
        std::cout << std::endl;
#endif
        
        delete this->impl;
    }
    

    void ResourceManager::addResource(Resource* resource) {
        assert(this->impl != nullptr);
        
        this->impl->resources.push_back(resource);
    }

    
    void ResourceManager::putResource(Resource* resource, const std::string &name)  {
        assert(this->impl != nullptr);
        
        if (name == "") {
            throw std::logic_error("ResourceManager::putResource: The name cannot be \"\". ");
        }
        
        // validate previous instance
		this->impl->namedResources[name] = resource;
    }
    

    void ResourceManager::removeResource(const std::string &name) {
        assert(this->impl != nullptr);

		auto &resources = this->impl->namedResources;
		auto pos = resources.find(name);

		if (pos != resources.end()) {
			pos->second->release();
			delete pos->second;
			resources.erase(name);
		}
    }
    
	
	void ResourceManager::removeResource(Resource* resource) {
        assert(this->impl != nullptr);
        
		resource->release();
		delete resource;

        this->impl->resources.remove(resource);
    }
}
