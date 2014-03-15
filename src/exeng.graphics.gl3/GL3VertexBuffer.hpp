/**
 * @file GL3VertexBuffer.hpp
 * @brief Definition of the OpenGL 3 VertexBuffer class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_GL3_GL3VERTEXBUFFER_HPP__
#define __EXENG_GRAPHICS_GL3_GL3VERTEXBUFFER_HPP__

#include <exeng/graphics/VertexBuffer.hpp>
#include <exeng/HeapBuffer.hpp>
#include "GL3.hpp"

namespace exeng { namespace graphics { namespace gl3 {
    class GL3GraphicsDriver;
    
    class GL3VertexBuffer : public VertexBuffer {
    public:
        GL3VertexBuffer(ResourceManager *factory, const VertexFormat &format, int count);
        
        virtual ~GL3VertexBuffer();
        
        virtual void allocate(const VertexFormat &format, int count);
        
        virtual void release();
        
        virtual bool isEmpty() const;
        
        virtual void* lock();
        
        virtual bool isLocked() const;
        
        virtual void unlock();
        
        virtual int getCount() const;
        
        virtual int getSize() const;
        
        virtual const VertexFormat& getFormat() const;
        
        inline int getName() const {
            return this->name;
        }
        
        inline int getVertexArrayId() const {
            return this->vertexArrayId;
        }
                        
        virtual TypeInfo getTypeInfo() const;
        
    private:
        ::GLuint vertexArrayId;
        ::GLuint name;
        bool locked;
        int count;
        VertexFormat format;
        
        HeapBuffer buffer;
    };
}}}

#endif //__EXENG_GRAPHICS_GL3_GL3VERTEXBUFFER_HPP__
