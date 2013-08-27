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
 * @brief Resource factory abstract base class.
 */
class EXENGAPI Resource;
class EXENGAPI ResourceFactory : public Object {
    friend class Resource;
public:
    ResourceFactory();
    
    virtual ~ResourceFactory();
    
protected:
    /**
     * @brief Add a resource to the internal list.
     */
    virtual void addResource(Resource* resource);
    
    /**
     * @brief Remove the resource from the resource factory.
     */
    virtual void removeResource(Resource* resource);
    
private:
    struct Private;
    Private *impl;
};
}

 
#endif //__EXENG_RESOURCEFACTORY_HPP__
