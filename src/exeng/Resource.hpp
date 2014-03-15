/**
 * @file Resource.hpp
 * @brief Defines the Resource abstract class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_RESOURCE_HPP__
#define __EXENG_RESOURCE_HPP__

#include <exeng/Object.hpp>
#include <exeng/Enum.hpp>
#include <exeng/TFlags.hpp>

namespace exeng {
    class EXENGAPI ResourceManager;
    /**
    * @brief Resource status enumeration 
    */
    struct ResourceStatus : public Enum {
        enum Enum {
            
            //! Usable state.
            Ready = 0x00000001,
            
            //! The internal data has been freed. Is the state for empty resources, also.
            Released = 0x00000002,
            
            //! Lost. Used when the parent factory changed some important status, and the internal data is no longer valid.
            Lost = 0x00000004,
            
            //! The resource is currently initialized.
            Initializing = 0x00000008
        };
        
        typedef TFlags<Enum> Flags;
    };


    /**
    * @brief Object with internal data asociated, dependent on another object.
    */
    class EXENGAPI Resource : public Object {    
        friend class ResourceManager;
        
    public:
        explicit Resource(ResourceManager *resourceFactory);
        
        virtual ~Resource();
        
        /**
         * @brief Release all the data associated with the resource, without deleting it.
         * Called by the resource factory when this one has been eliminated or terminated on any form.
         */
        virtual void release();
        
        /**
         * @brief Restore the resource to a usable state. Only used when the resource have
         * the 'Lost' status flag.
         */
        virtual void restore();
        
        /**
         * @brief Get the current states of the resource.
         */
        virtual ResourceStatus::Flags getStatusFlags() const;
        
		virtual ResourceManager* getResourceManager();

		virtual const ResourceManager* getResourceManager() const;

    protected:
        ResourceManager *resourceManager;
    };
}

#endif // __EXENG_RESOURCE_HPP__
