
#ifndef __EXENG_GRAPHICS_GL3_GL3VERTEXBUFFER_HPP__
#define __EXENG_GRAPHICS_GL3_GL3VERTEXBUFFER_HPP__

#include <memory>
#include <xe/Buffer.hpp>
#include <xe/HeapBuffer.hpp>
#include "GL3.hpp"

namespace xe { namespace gfx { namespace gl3 {

    class BufferGL3 :  public Buffer {
    public:
        /* Buffer overrides */
        BufferGL3(const int size, GLenum target);
        virtual ~BufferGL3();

        virtual const void* getPointer() const override;

        virtual int getSize() const override;

		virtual int getHandle() const override;

        virtual void setData(const void *data, const int size, const int dataOffset, const int bufferOffset) override;
        virtual void getData(void* data, const int size, const int dataOffset, const int bufferOffset) const override;

    public:
        /* Object overrides */
        virtual TypeInfo getTypeInfo() const override;
        
    public:
        GLuint getBufferId() const {
            return this->bufferId;
        }

        GLenum getTarget() const {
            return this->target;
        }

    private:
        ::GLuint bufferId = 0;
        ::GLenum target = 0;
        
        HeapBufferPtr cacheBuffer;
    };
}}}

#endif
