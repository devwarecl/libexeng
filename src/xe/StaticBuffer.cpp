
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

	void StaticBuffer::getData(void* data, const int dataSize, const int dataOffset, const int bufferOffset) const {
#if defined (EXENG_DEBUG)
		if (bufferOffset + dataSize > this->getSize()) {
			EXENG_THROW_EXCEPTION("Buffer overrun.");
		}
#endif
		const std::uint8_t* srcData = static_cast<const std::uint8_t*>(this->data) + bufferOffset;
		std::uint8_t* dstData = static_cast<std::uint8_t*>(data) + dataOffset;

		std::memcpy(dstData, srcData, dataSize);
	}

	void StaticBuffer::setData(const void *data, const int dataSize, const int dataOffset, const int bufferOffset) {
#if defined (EXENG_DEBUG)
		if (bufferOffset + dataSize > this->getSize()) {
			EXENG_THROW_EXCEPTION("Buffer overrun.");
		}
#endif
		const std::uint8_t* srcData = static_cast<const std::uint8_t*>(data) + dataOffset;
		std::uint8_t* dstData = static_cast<std::uint8_t*>(this->data) + bufferOffset;
		std::memcpy(dstData, srcData, dataSize);
	}
}
