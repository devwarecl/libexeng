/**
 * @file ResourceManager.hpp
 * @brief Defines the ResourceManager class.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_RESOURCEMANAGER_HPP__
#define __EXENG_RESOURCEMANAGER_HPP__

#include <exeng/Object.hpp>

namespace exeng {
    /**
     * @brief Resource factory abstract base class.
     */
    class EXENGAPI Resource;
    class EXENGAPI ResourceManager : public Object {
        friend class Resource;
    public:
        ResourceManager();
        
        virtual ~ResourceManager();
        
        /**
         * @brief Add a resource to the internal list.
         * 
         * The ResourceManager is now the manager of the object
         */
        void putResource(Resource* resource, const std::string &name);
        
        
        /**
         * @brief Add a resource to the internal list.
         * 
         * The ResourceManager is now the manager of the object
         */
        void addResource(Resource* resource);
        
        
        /**
         * @brief Remove the resource from the resource factory.
         */
        void removeResource(Resource* resource);
        
        /**
         * @brief Remove the resource from the resource factory.
         */
        void removeResource(const std::string &name);
        
    private:
        struct Private;
        Private *impl;
    };
}
 
#endif //__EXENG_RESOURCEFACTORY_HPP__
