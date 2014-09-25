
#ifndef __EXENG_GRAPHICS_GL3_GL3INDEXBUFFER_HPP__
#define __EXENG_GRAPHICS_GL3_GL3INDEXBUFFER_HPP__

#include <exeng/HeapBuffer.hpp>
#include <exeng/graphics/IndexBuffer.hpp>
#include "GL3.hpp"

namespace exeng { namespace graphics { namespace gl3 {

    //class GL3IndexBuffer : public IndexBuffer {
    //public:
    //    GL3IndexBuffer();
    //    GL3IndexBuffer(IndexFormat::Enum indexFormat, int indexCount);
    //    virtual ~GL3IndexBuffer();

    //    virtual void allocate(IndexFormat::Enum indexFormat, int indexCount) override;
    //    
    //    virtual void release() override;
    //        
    //    virtual bool isEmpty() const override;
    //        
    //    virtual void* lock() override;
    //    
    //    virtual bool isLocked() const override;
    //    
    //    virtual void unlock() override;
    //    
    //    virtual int getCount() const override;
    //    
    //    virtual IndexFormat::Enum getFormat() const override;

    //private:
    //    GLuint indexBufferId = 0;
    //    IndexFormat::Enum indexFormat = IndexFormat::Index32;
    //    int count = 0;
    //    bool locked = false;
    //    HeapBuffer buffer;
    //};
}}}

#endif
