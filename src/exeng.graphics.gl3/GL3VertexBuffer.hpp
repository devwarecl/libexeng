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
    //class GL3GraphicsDriver;
    //
    //class GL3VertexBuffer : public Buffer {
    //    /* VertexBuffer overrides */
    //public:
    //    virtual ~GL3VertexBuffer();
    //    virtual bool isLocal() const override;
    //    virtual void* getDataPtr() override;
    //    virtual const void* getDataPtr() const override;
    //    virtual void write() override;
    //    virtual void read() override;
    //    virtual std::uint64_t getHandle() const override;
    //    virtual std::uint32_t getSize() const override;
    //    virtual void setData(const void* dataSrc, const std::uint32_t size) override;
    //    virtual void getData(void* dataDst, const std::uint32_t size, const std::uint32_t offset) const override;

    //    /* Object overrides */
    //public:
    //    virtual TypeInfo getTypeInfo() const override;
    //    
    //public:
    //    inline int getBufferId() const {
    //        return this->bufferId;
    //    }

    //    void allocate(const VertexFormat &format, int count);
    //    void release();

    //private:
    //    ::GLuint bufferId = 0;
    //    int count = 0;

    //    HeapBuffer cacheBuffer;
    //};
}}}

#endif //__EXENG_GRAPHICS_GL3_GL3VERTEXBUFFER_HPP__
