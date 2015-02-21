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

#include "Resource.hpp"

namespace exeng {
    Resource::~Resource() {}

    void Resource::release() 
	{
		throw std::runtime_error("Resource::release: Not Implemented");
	}
        
    void Resource::restore() 
	{
		throw std::runtime_error("Resource::restore: Not Implemented");
	}

	std::uint64_t Resource::getHandle() const 
	{
		throw std::runtime_error("Resource::getHandle: Not Implemented");
	}

    ResourceStatus::Flags Resource::getResourceStatus() const
	{
		throw std::runtime_error("Resource::getResourceStatus: Not Implemented");
	}
}
