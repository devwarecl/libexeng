/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "HeapBuffer.hpp"

#include <exeng/Exception.hpp>

#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <memory>

namespace exeng {
	HeapBuffer::HeapBuffer(const int size) {
		void* data = std::malloc(size);

		if (!data) {
			EXENG_THROW_EXCEPTION("No enough memory.");
		}

		if (data) {
			this->data = data;
			this->size = size;
		}
	}

	HeapBuffer::~HeapBuffer() {
		if (this->data) {
			std::free(this->data);
		}
	}

	void HeapBuffer::getData(void* data, const int size, const int dataOffset, const int bufferOffset) const {
		const std::uint8_t* srcData = static_cast<const std::uint8_t*>(this->data) + bufferOffset;
		std::uint8_t* dstData = static_cast<std::uint8_t*>(data) + dataOffset;

		std::memcpy(dstData, srcData, size);
	}

	void HeapBuffer::setData(const void *data, const int size, const int dataOffset, const int bufferOffset) {
		const std::uint8_t* srcData = static_cast<const std::uint8_t*>(data) + dataOffset;
		std::uint8_t* dstData = static_cast<std::uint8_t*>(this->data) + bufferOffset;
		std::memcpy(dstData, srcData, size);
	}
}

namespace exeng {
    HeapBuffer2::HeapBuffer2() {}

    HeapBuffer2::HeapBuffer2(const std::uint32_t size) {
        this->allocate(size);
    }

    Buffer2::Flags HeapBuffer2::getFlags() const {
        if (this->data) {
            return Buffer2::Local;
        } else {
            return Buffer2::Local | Buffer2::Empty;
        }
    }

    void HeapBuffer2::allocate(const std::uint32_t size) {
        this->release();

        this->data = std::malloc(size);
        this->size = size;
    }

    void HeapBuffer2::release() {
        if (this->data) {
            std::free(this->data);

            this->data = nullptr;
            this->size = 0;
        }
    }

    HeapBuffer2::~HeapBuffer2() {
        this->release();
    }

    std::uint32_t HeapBuffer2::getSize() const {
        return this->size;
    }

    void* HeapBuffer2::getDataPtr() {
        return this->data;
    }

    const void* HeapBuffer2::getDataPtr() const {
        return this->data;
    }

    void HeapBuffer2::write() {}
    void HeapBuffer2::read() {}

    std::uint64_t HeapBuffer2::getHandle() const {
        return reinterpret_cast<std::uint64_t>(this->data);
    }

    void HeapBuffer2::setData(const void* dataSrc, const std::uint32_t size) {
        this->allocate(size);
        std::memcpy(this->data, dataSrc, size);
    }

    void HeapBuffer2::getData(void* dataDst, const std::uint32_t size, const std::uint32_t offset) const {
        std::memcpy(dataDst, reinterpret_cast<std::uint8_t*>(this->data) + offset, size );
    }
}
