/**
 * @file Resource.cpp
 * @brief Implements some method of the Resource abstact class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <exeng/Resource.hpp>
#include <exeng/ResourceFactory.hpp>

namespace exeng {
Resource::Resource(ResourceFactory *resourceFactory) : creator(resourceFactory) {
}


Resource::~Resource() {
    if (this->creator != nullptr) {
        this->creator->onResourceDestruction(this);
    }
}


ResourceFactory* Resource::getResourceFactory() {
    return this->creator;
}


const ResourceFactory* Resource::getResourceFactory() const {
    return this->creator;
}


void Resource::restore() {
    
}


ResourceStatus::Flags Resource::getStatusFlags() const {
    return ResourceStatus::Ready;
}
}
