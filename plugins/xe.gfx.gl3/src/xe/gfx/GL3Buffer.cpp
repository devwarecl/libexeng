
#include "GL3Buffer.hpp"
#include "GL3BufferStatus.hpp"
#include "GL3Debug.hpp"
#include <stdexcept>

namespace xe { namespace gfx { namespace gl3 {

    GL3Buffer::GL3Buffer(const int size, GLenum target) {
		this->cacheBuffer = std::make_unique<HeapBuffer>(size);
		this->target = target;

		::glGenBuffers(1, &this->bufferId);
        ::glBindBuffer(this->target, this->bufferId);
        ::glBufferData(this->target, size, nullptr, GL_DYNAMIC_DRAW);

		::glBindBuffer(this->target, 0);

		assert(this->bufferId);

		GL3_CHECK();
	}

    GL3Buffer::~GL3Buffer() {
		assert(this);
		assert(this->bufferId);

		::glDeleteBuffers(1, &this->bufferId);
	}

	const void* GL3Buffer::getPointer() const {
		assert(this);
		assert(this->cacheBuffer.get());

		return this->cacheBuffer->getPointer();
	}

	int GL3Buffer::getSize() const {
		assert(this);
		assert(this->cacheBuffer.get());

		return this->cacheBuffer->getSize();
	}

	int GL3Buffer::getHandle() const {
		assert(this);

		return this->bufferId;
	}

    void GL3Buffer::setData(const void *data, const int size, const int dataOffset, const int bufferOffset) {
		assert(this);
		assert(this->cacheBuffer.get());

		// BufferStatus status(this->target);

		::glBindBuffer(this->target, this->bufferId);
		::glBufferSubData(this->target, bufferOffset, size, data);
		::glBindBuffer(this->target, 0);

		this->cacheBuffer->setData(data, size, dataOffset, bufferOffset);

		GL3_CHECK();
	}

    void GL3Buffer::getData(void* data, const int size, const int dataOffset, const int bufferOffset) const {
		assert(this);

		this->cacheBuffer->getData(data, size, dataOffset, bufferOffset);

		// GL3_CHECK();
	}

	TypeInfo GL3Buffer::getTypeInfo() const {
		assert(this);
		
        return TypeId<GL3Buffer>();
    }
}}}
