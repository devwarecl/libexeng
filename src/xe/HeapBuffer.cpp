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

#include <xe/Exception.hpp>

#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <memory>

namespace xe {
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

	void HeapBuffer::read(void* data, const int size, const int dataOffset, const int bufferOffset) const {
#if defined (EXENG_DEBUG)
		if (bufferOffset + size > this->getSize()) {
			EXENG_THROW_EXCEPTION("Buffer overrun.");
		}
#endif
		const std::uint8_t* srcData = static_cast<const std::uint8_t*>(this->data) + bufferOffset;
		std::uint8_t* dstData = static_cast<std::uint8_t*>(data) + dataOffset;

		std::memcpy(dstData, srcData, size);
	}

	void HeapBuffer::write(const void *data, const int size, const int dataOffset, const int bufferOffset) {
#if defined (EXENG_DEBUG)
		if (bufferOffset + size > this->getSize()) {
			EXENG_THROW_EXCEPTION("Buffer overrun.");
		}
#endif
		const std::uint8_t* srcData = static_cast<const std::uint8_t*>(data) + dataOffset;
		std::uint8_t* dstData = static_cast<std::uint8_t*>(this->data) + bufferOffset;
		std::memcpy(dstData, srcData, size);
	}
}
