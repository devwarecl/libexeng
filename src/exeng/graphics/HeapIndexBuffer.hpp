/**
 * @file HeapIndexBuffer.hpp
 * @brief Definition of the HeapIndexBuffer class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_HEAPINDEXBUFFER_HPP__
#define __EXENG_GRAPHICS_HEAPINDEXBUFFER_HPP__

#include <exeng/graphics/IndexBuffer.hpp>

namespace exeng { namespace graphics {
    /**
     * @brief IndexBuffer allocated on heap memory.
     */
    class EXENGAPI HeapIndexBuffer : public IndexBuffer {
    public:            
        HeapIndexBuffer(ResourceManager *factory);
            
        HeapIndexBuffer(ResourceManager *factory, IndexFormat indexFormat, int indexCount);
            
        virtual ~HeapIndexBuffer();
            
        virtual void allocate(IndexFormat indexFormat, int indexCount);
            
        virtual void release();
            
        virtual bool isEmpty() const;
            
        virtual void* lock();
            
        virtual bool isLocked() const;
            
        virtual void unlock();
            
        virtual int getCount() const;
            
        virtual IndexFormat getFormat() const;
            
    private:
        struct Private;
        Private *impl;
    };
}}


#endif // __EXENG_GRAPHICS_HEAPINDEXBUFFER_HPP__
