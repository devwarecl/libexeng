/**
 * @file Buffer.hpp
 * @brief Define the Buffer abstract class.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_BUFFER_HPP__
#define __EXENG_BUFFER_HPP__

#include <exeng/Object.hpp>

namespace exeng {
    /**
     * @brief Raw data container.
     */
    class EXENGAPI Buffer : public Object {
    public:
        virtual ~Buffer();
        
        /**
         * @brief Lock the buffer, and gets a pointer to the buffer data, 
         * in read-write usage mode.
         */
        virtual void* lock() = 0;
        
        /**
         * @brief Lock the buffer, and gets a pointer to the buffer data, 
         * in read-only usage mode.
         */
        virtual const void* lock() const = 0;
        
        /**
         * @brief Unlocks the buffer, enabling the data to be modified again.
         */
        virtual void unlock() = 0;
        
        /**
         * @brief Unlocks the buffer, enabling the data to be modified again. 
         * Used in constant instances.
         */
        virtual void unlock() const = 0;
        
        /**
         * @brief Check if the buffer is locked.
         */
        virtual bool isLocked() const = 0;
        
        /**
         * @brief Check if the buffer has available data.
         */
        virtual bool isEmpty() const = 0;
        
        /**
         * @brief Gets the size of the buffer, in bytes.
         */
        virtual int getSize() const = 0;
    };
}

#endif // __EXENG_BUFFER_HPP__
