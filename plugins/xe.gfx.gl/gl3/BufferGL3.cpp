
#include "BufferGL3.hpp"
#include "BufferStatusGL3.hpp"
#include "DebugGL3.hpp"
#include <stdexcept>
#include <iostream>

namespace xe { namespace gfx { namespace gl3 {

    BufferGL3::BufferGL3(const int size, GLenum target) {
		this->cacheBuffer = std::make_unique<HeapBuffer>(size);
		this->target = target;

		::glGenBuffers(1, &this->bufferId);
        ::glBindBuffer(this->target, this->bufferId);
        ::glBufferData(this->target, size, nullptr, GL_DYNAMIC_DRAW);

		::glBindBuffer(this->target, 0);

		assert(this->bufferId);

		GL3_CHECK();
	}

    BufferGL3::~BufferGL3() {
		assert(this);
		assert(this->bufferId);

		::glDeleteBuffers(1, &this->bufferId);
	}

    void* BufferGL3::lock(BufferUsage::Enum mode) {
        void *result_cache_ptr = cacheBuffer->lock(mode);

        if (mode&BufferUsage::Write) {
            cache_ptr = result_cache_ptr;

        } else {
            cache_ptr = nullptr;
        }

        return result_cache_ptr;
    }

    void BufferGL3::unlock() {
        if (cache_ptr) {
            ::glBindBuffer(this->target, this->bufferId);
		    ::glBufferSubData(this->target, 0, cacheBuffer->getSize(), cache_ptr);
		    ::glBindBuffer(this->target, 0);

            // display vertex data

#if defined(EXENG_DEBUG)
            std::cout << std::endl;

            std::cout << std::endl;
            float *values = (float *)cache_ptr;
            const int value_count = cacheBuffer->getSize() / 4;

            for (int i=0; i<value_count; i++) {
                std::cout << values[i] << ", ";

                if ( (i+1) % 8 == 0) {
                    std::cout << std::endl;
                }
            }
#endif

            cache_ptr = nullptr;

            GL3_CHECK();
        }

        return cacheBuffer->unlock();
    }

    const void* BufferGL3::lock() const {
        return cacheBuffer->lock();
    }

    void BufferGL3::unlock() const {
        cacheBuffer->unlock();
    }

	int BufferGL3::getSize() const {
		assert(this);
		assert(this->cacheBuffer.get());

		return this->cacheBuffer->getSize();
	}

	int BufferGL3::getHandle() const {
		assert(this);

		return this->bufferId;
	}

    void BufferGL3::write(const void *data, const int size, const int dataOffset, const int bufferOffset) {
		assert(this);
		assert(this->cacheBuffer.get());

		// BufferStatus status(this->target);

		::glBindBuffer(this->target, this->bufferId);
		::glBufferSubData(this->target, bufferOffset, size, data);
		::glBindBuffer(this->target, 0);

		this->cacheBuffer->write(data, size, dataOffset, bufferOffset);

		GL3_CHECK();
	}

    void BufferGL3::read(void* data, const int size, const int dataOffset, const int bufferOffset) const {
		assert(this);

		this->cacheBuffer->read(data, size, dataOffset, bufferOffset);

		// GL3_CHECK();
	}

	TypeInfo BufferGL3::getTypeInfo() const {
		assert(this);
		
        return TypeId<BufferGL3>();
    }
}}}
