/**
 * @file Resource.cpp
 * @brief Implements some of the methods of the Resource abstact class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <iostream>
#include <exeng/Resource.hpp>
#include <exeng/ResourceFactory.hpp>

namespace exeng {
Resource::Resource(ResourceFactory *resourceFactory_) : resourceFactory(resourceFactory_) {
}


Resource::~Resource() {
    if (this->resourceFactory != nullptr) {
        this->resourceFactory->removeResource(this);
    }
}


ResourceFactory* Resource::getResourceFactory() {
    return this->resourceFactory;
}


const ResourceFactory* Resource::getResourceFactory() const {
    return this->resourceFactory;
}


void Resource::restore() {
    std::cout << "Resource::restore: Not implemented." << std::endl;
}

void Resource::release() {
    std::cout << "Resource::release: Not implemented." << std::endl;
}

ResourceStatus::Flags Resource::getStatusFlags() const {
    return ResourceStatus::Ready;
}
}
