/**
 * @file HeapVertexBuffer.hpp
 * @brief Definition of the HeapVertexBuffer class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_HEAPVERTEXBUFFER_HPP__
#define __EXENG_GRAPHICS_HEAPVERTEXBUFFER_HPP__

#include <exeng/graphics/VertexBuffer.hpp>

namespace exeng { namespace graphics {
    
    /**
	 * @brief VertexBuffer allocated on heap memory. Useful for
     * software-based rasterizers.
     */
/*    class EXENGAPI HeapVertexBuffer : public VertexBuffer {
    public:
        HeapVertexBuffer(ResourceManager *resourceFactory);
            
        HeapVertexBuffer(ResourceManager *resourceFactory, const VertexFormat &format, int count);
            
        virtual ~HeapVertexBuffer();
            
        virtual void allocate(const VertexFormat &format, int count);
            
        virtual void release();
            
        virtual bool isEmpty() const;
            
        virtual void* lock();
            
        virtual bool isLocked() const;
            
        virtual void unlock();
            
        virtual int getCount() const;
            
        virtual int geSize() const;
            
        virtual const VertexFormat& getFormat() const;
            
    private:
        struct Private;
        Private *impl;
    };   */     
}}

#endif // __EXENG_GRAPHICS_HEAPVERTEXBUFFER_HPP__
