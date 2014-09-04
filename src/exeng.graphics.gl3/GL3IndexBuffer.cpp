
#include "GL3IndexBuffer.hpp"
#include "GL3Utils.hpp"
#include "GL3BufferStatus.hpp"

namespace exeng { namespace graphics { namespace gl3 {
    GL3IndexBuffer::GL3IndexBuffer() {
    }

    GL3IndexBuffer::GL3IndexBuffer(IndexFormat::Enum indexFormat, int indexCount) {
        this->allocate(indexFormat, indexCount);
    }

    GL3IndexBuffer::~GL3IndexBuffer() {
        this->release();
    }

    void GL3IndexBuffer::allocate(IndexFormat::Enum indexFormat, int indexCount) {
        this->release();

        const int size = IndexFormat::geSize(indexFormat) * indexCount;
        this->buffer.allocate(size);

        BufferStatus<GL_ELEMENT_ARRAY_BUFFER> status;

        ::glGenBuffers(1, &this->indexBufferId);
        ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
        ::glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
    }

    void GL3IndexBuffer::release() {
        ::glDeleteBuffers(1, &this->indexBufferId);

        this->count = false;
        this->buffer.release();
    }

    bool GL3IndexBuffer::isEmpty() const {
        return this->count == 0;
    }
            
    void* GL3IndexBuffer::lock() {
        this->locked = true;

        return this->buffer.lock();
    }
        
    bool GL3IndexBuffer::isLocked() const {
        return this->locked;
    }
    
    void GL3IndexBuffer::unlock() {
        this->locked = false;

        BufferStatus<GL_ELEMENT_ARRAY_BUFFER> status;

        const std::size_t size = this->count * IndexFormat::geSize(this->indexFormat);

        ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
        ::glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, this->buffer.getPtr());

        this->buffer.unlock();
    }
    
    int GL3IndexBuffer::getCount() const {
        return this->count;
    }
    
    IndexFormat::Enum GL3IndexBuffer::getFormat() const {
        return this->indexFormat;
    }
}}}
