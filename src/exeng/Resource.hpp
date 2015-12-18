///**
// * @file Resource.hpp
// * @brief Defines the Resource abstract class.
// */
//
//
///*
// * Copyright (c) 2013 Felipe Apablaza.
// *
// * The license and distribution terms for this file may be
// * found in the file LICENSE in this distribution.
// */
//
//#ifndef __EXENG_RESOURCE_HPP__
//#define __EXENG_RESOURCE_HPP__
//
//#include <cstdint>
//#include <memory>
//#include <exeng/Object.hpp>
//#include <exeng/Enum.hpp>
//#include <exeng/TFlags.hpp>
//
//namespace exeng {
//    /**
//    * @brief Resource status enumeration 
//    */
//    struct ResourceStatus : public Enum {
//        enum Enum {
//            //! Usable state.
//            Ready = 1,
//            
//            //! The internal data has been freed. Is the state for empty resources, also.
//            Released = 2,
//            
//            //! Lost. Used when the parent factory changed some important status, and the internal data is no longer valid.
//            Lost = 4,
//            
//            //! The resource is currently initialized.
//            Initializing = 8
//        };
//        
//        typedef TFlags<Enum> Flags;
//    };
//
//    /**
//     * @brief Object with special memory requerimients.
//     */
//    class EXENGAPI Resource : public Object {    
//    public:
//        virtual ~Resource();
//        
//        /**
//         * @brief Release all the data associated with the resource.
//         */
//        virtual void release();
//        
//        /**
//         * @brief Restore the resource to a usable state, in case the internal handler has been released.
//         */
//        virtual void restore();
//
//		/**
//		 * @brief Get the native handle of the resource.
//		 */
//		virtual int getHandle() const;
//
//        /**
//         * @brief Get the current states of the resource.
//         */
//        virtual ResourceStatus::Flags getResourceStatus() const;
//    };
//
//	typedef std::unique_ptr<Resource> ResourcePtr;
//}
//
//#endif // __EXENG_RESOURCE_HPP__
