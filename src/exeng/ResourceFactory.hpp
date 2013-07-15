/**
 * @file ResourceFactory.hpp
 * @brief Defines the ResourceFactory class.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_RESOURCEFACTORY_HPP__
#define __EXENG_RESOURCEFACTORY_HPP__

#include <exeng/Object.hpp>

namespace exeng {

/**
 * @brief Resource factory
 */
class EXENGAPI Resource;
class EXENGAPI ResourceFactory : public Object {
public:
    virtual ~ResourceFactory();
    
    /**
     * @brief Notify the factory of the destruction of the object
     */
    virtual void onResourceDestruction(Resource* resource) = 0;
};
}

 
#endif //__EXENG_RESOURCEFACTORY_HPP__
