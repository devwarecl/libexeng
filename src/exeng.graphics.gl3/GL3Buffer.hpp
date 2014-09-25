
#ifndef __EXENG_GRAPHICS_GL3_GL3VERTEXBUFFER_HPP__
#define __EXENG_GRAPHICS_GL3_GL3VERTEXBUFFER_HPP__

#include <exeng/Buffer.hpp>
#include <exeng/HeapBuffer.hpp>
#include "GL3.hpp"

namespace exeng { namespace graphics { namespace gl3 {
    class GL3Buffer :  public Buffer {
    public:
        /* Buffer overrides */
        GL3Buffer(GLenum target, const std::uint32_t size);
        virtual ~GL3Buffer();

        virtual void allocate(const std::uint32_t size) override;
        virtual void release() override;
        virtual Flags getFlags() const override;
        virtual void* getDataPtr() override;
        virtual const void* getDataPtr() const override;
        virtual void write() override;
        virtual void read() override;
        virtual std::uint64_t getHandle() const override;
        virtual std::uint32_t getSize() const override;
        virtual void setData(const void* dataSrc, const std::uint32_t size) override;
        virtual void getData(void* dataDst, const std::uint32_t size, const std::uint32_t offset) const override;

    public:
        /* Object overrides */
        virtual TypeInfo getTypeInfo() const override;
        
    public:
        inline GLuint getBufferId() const {
            return this->bufferId;
        }

        inline GLenum getTarget() const {
            return this->target;
        }

    private:
        ::GLuint bufferId = 0;
        ::GLenum target = 0;
        int count = 0;

        HeapBuffer cacheBuffer;
    };
}}}

#endif
