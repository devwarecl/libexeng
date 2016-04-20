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
#include <cstring>#
#include <cassert>
#include <memory>

namespace xe {

	void HeapBuffer::alloc(const int size) {
		free();

		std::uint8_t* data = static_cast<std::uint8_t*>(std::malloc(size));

		assert(data);

		if (data) {
			this->data = data;
			this->size = size;
		}
	}

	void HeapBuffer::free() {
		if (data) {
			std::free(data);
			data = nullptr;
			size = 0;
		}
	}

	void HeapBuffer::read(void* destination, const int size, const int offset, const int destination_offset) const {
		assert(destination);
		assert(offset + size < this->getSize());

		std::memcpy (
			static_cast<std::uint8_t*>(destination) + destination_offset, 
			data + offset, 
			size
		);
	}

	void HeapBuffer::write(const void *source, const int size, const int offset, const int source_offset) {
		assert(source);
		assert(offset + size < this->getSize());

		std::memcpy ( 
			data + offset, 
			static_cast<const std::uint8_t*>(source) + source_offset, 
			size
		);
	}
}
