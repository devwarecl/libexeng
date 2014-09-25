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

#include <exeng/Resource.hpp>
#include <exeng/Enum.hpp>
#include <stdexcept>

namespace exeng { namespace graphics {
    ///**
    // *  @brief Valid formats for a IndexBuffer
    // */
    //struct IndexFormat : public Enum {
    //    enum Enum {
    //        Index16=16,
    //        Index32=32
    //    };
    //    
    ////     inline static std::size_t getSize(IndexFormat::Enum format)  {
    ////         return format;
    ////     }
    //// };
    
    /**
     * @brief Memory area dedicated for Index data
     */
    // class EXENGAPI IndexBuffer : public Resource {
    // public:
        // IndexBuffer();
        // IndexBuffer(ResourceManager* factory);
        
        /**
         * @brief 
         */
        // virtual ~IndexBuffer();
        
        /**
         * @brief 
         */
        // virtual void allocate(IndexFormat::Enum indexFormat, int indexCount) = 0;
            
        /**
         * @brief 
         */
        // virtual void release() = 0;
            
        /**
         * @brief 
         */
        // virtual bool isEmpty() const = 0;
            
        /**
         * @brief 
         */
        // virtual void* lock() = 0;
            
        /**
         * @brief 
         */
        // virtual bool isLocked() const = 0;
            
        /**
         * @brief 
         */
        // virtual void unlock() = 0;
        
        /**
         * @brief 
         */
        // virtual int getCount() const = 0;
            
        /**
         * @brief 
         */
        // virtual IndexFormat::Enum getFormat() const = 0;
        // virtual void setData(const void* srcData, const int size) = 0;
        // virtual void getData(void* dstData);
    // };
}}

#endif  // __EXENG_GRAPHICS_INDEXBUFFER_HPP__
