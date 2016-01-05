
#include "StaticBuffer.hpp"

#include <xe/Exception.hpp>

namespace xe {
	StaticBuffer::StaticBuffer(void* data, const int dataSize) {
		this->data = data;
		this->dataSize = dataSize;
	}

	int StaticBuffer::getHandle() const {
		return reinterpret_cast<int>(this);
	}

	int StaticBuffer::getSize() const {
		return this->dataSize;
	}
	
	const void* StaticBuffer::getPointer() const {
		return this->data;
	}
}
