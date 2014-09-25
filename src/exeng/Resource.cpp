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
#include <stdexcept>
#include <exeng/Resource.hpp>
#include <exeng/ResourceManager.hpp>

namespace exeng {
    Resource::Resource() {}

    Resource::~Resource() {}
    
    void Resource::restore() {
        // throw std::logic_error("Resource::restore: Is not implemented.");
    }

    void Resource::release() {
        // throw std::logic_error("Resource::release: Is not implemented.");
    }
    
    ResourceStatus::Flags Resource::getStatusFlags() const {
        return ResourceStatus::Ready;
    }
}
