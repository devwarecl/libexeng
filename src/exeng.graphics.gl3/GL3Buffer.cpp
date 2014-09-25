
#include "GL3Buffer.hpp"
#include "GL3BufferStatus.hpp"

namespace exeng { namespace graphics { namespace gl3 {

    GL3Buffer::GL3Buffer(GLenum target_, const std::uint32_t size) : target(target_) {
        this->allocate(size);
    }

    GL3Buffer::~GL3Buffer() {
        this->release();
    }

    
    void GL3Buffer::allocate(const std::uint32_t size) {
        this->release();

        BufferStatus status(target);

        ::glGenBuffers(1, &this->bufferId);
        ::glBindBuffer(this->target, this->bufferId);
        ::glBufferData(this->target, size, nullptr, GL_DYNAMIC_DRAW);

        this->cacheBuffer.allocate(size);
    }

    void GL3Buffer::release() {
        if (this->bufferId) {
            ::glDeleteBuffers(1, &this->bufferId);
            this->bufferId = 0;
        }

        this->cacheBuffer.release();
    }

    Buffer::Flags GL3Buffer::getFlags() const  {
        Buffer::Flags flags = this->cacheBuffer.getFlags();
        flags.activate(Buffer::Local, false);

        return flags;
    }

    void* GL3Buffer::getDataPtr() {
        return this->cacheBuffer.getDataPtr();
    }

    const void* GL3Buffer::getDataPtr() const {
        return this->cacheBuffer.getDataPtr();
    }

    void GL3Buffer::write() {
        BufferStatus status(this->target);

        ::glBindBuffer(this->target, this->bufferId);
        ::glBufferSubData(this->target, 0, this->cacheBuffer.getSize(), this->cacheBuffer.getDataPtr());
    }

    void GL3Buffer::read() {
        throw std::bad_exception("GL3Buffer::read: Not implemented.");
    }

    std::uint64_t GL3Buffer::getHandle() const {
        return this->bufferId;
    }

    std::uint32_t GL3Buffer::getSize() const {
        return this->cacheBuffer.getSize();
    }

    void GL3Buffer::setData(const void* dataSrc, const std::uint32_t size) {
        this->cacheBuffer.setData(dataSrc, size);
        this->write();
    }

    void GL3Buffer::getData(void* dataDst, const std::uint32_t size, const std::uint32_t offset) const {
        throw std::bad_exception("GL3Buffer::getData: Not implemented.");
    }

    TypeInfo GL3Buffer::getTypeInfo() const {
        return TypeId<GL3Buffer>();
    }
}}}
