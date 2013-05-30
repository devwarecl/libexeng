/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_INDEXBUFFER_HPP__
#define __EXENG_GRAPHICS_INDEXBUFFER_HPP__

#include <exeng/Object.hpp>
#include <stdexcept>

namespace exeng {
    namespace graphics {
        
        /**
         *  @brief Valid formats for a IndexBuffer
         */
        enum class IndexFormat {
            Index16=16,
            Index32=32
        };
        
        /**
         * @brief Memory area dedicated for IndexData
         */
        class EXENGAPI IndexBuffer : public Object {
        public:
            /**
             * @brief 
             */
            virtual ~IndexBuffer();
            
            /**
             * @brief 
             */
            virtual void allocate(IndexFormat indexFormat, int indexCount) = 0;
            
            /**
             * @brief 
             */
            virtual void release() = 0;
            
            /**
             * @brief 
             */
            virtual bool isEmpty() const = 0;
            
            /**
             * @brief 
             */
            virtual void* lock() = 0;
            
            /**
             * @brief 
             */
            virtual bool isLocked() const = 0;
            
            /**
             * @brief 
             */
            virtual void unlock() = 0;
            
            
            /**
             * @brief 
             */
            virtual int getCount() const = 0;
            
            /**
             * @brief 
             */
            virtual IndexFormat getFormat() const = 0;
        };
    }
}

#endif  // __EXENG_GRAPHICS_INDEXBUFFER_HPP__
