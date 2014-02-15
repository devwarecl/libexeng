/**
 * @file ResourceFactory.cpp
 * @brief Implement the resource factory methods
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <list>
#include <cassert>
#include <iostream>
#include <exeng/Resource.hpp>
#include <exeng/ResourceFactory.hpp>

namespace exeng {
    struct ResourceFactory::Private {
        std::list<Resource*> resources;
    };


    ResourceFactory::ResourceFactory() : impl(new ResourceFactory::Private()) {
        assert(this->impl != nullptr);
    }


    ResourceFactory::~ResourceFactory() {
        assert(this->impl != nullptr);
        
#if defined (EXENG_DEBUG)
        std::cout << "ResourceFactory::~ResourceFactory: Releasing ";
        std::cout << this->impl->resources.size() << " objects:" << std::endl;
#endif
        
        for (Resource *resource : this->impl->resources) {
            assert(resource->resourceFactory == this);
#if defined (EXENG_DEBUG)
            std::cout << "    " << resource->toString() << std::endl;
#endif
            resource->resourceFactory = nullptr;
            resource->release();
        }
        
        this->impl->resources.clear();
        
#if defined (EXENG_DEBUG)
        std::cout << std::endl;
#endif
        
        delete this->impl;
    }


    void ResourceFactory::addResource(Resource* resource) {
        assert(this->impl != nullptr);
        
        this->impl->resources.push_back(resource);
    }


    void ResourceFactory::removeResource(Resource* resource) {
        assert(this->impl != nullptr);
        
        this->impl->resources.remove(resource);
    }
}
