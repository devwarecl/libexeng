
#include "VertexArray.hpp"

namespace xe { namespace gfx {

	VertexArray::VertexArray(void *data, const VertexFormat *format) {
		assert(data);
		assert(format);
		assert(format->getSize() > 0);

		this->format = format;
		this->data = reinterpret_cast<std::uint8_t*>(data);
	}

	const int VertexArray::computeOffset(const int index, const VertexAttrib::Enum attrib) const {
		const int attribOffset = this->format->getAttribOffset(attrib);

		if (attribOffset == VertexFormat::InvalidOffset) {
			return VertexFormat::InvalidOffset;
		}

		const int vertexSize = this->format->getSize();
		const int offset = index * vertexSize + attribOffset;

		return offset;
	}

	std::uint8_t* VertexArray::getAttribPtr(const int index, const VertexAttrib::Enum attrib) {
		const int offset = this->computeOffset(index, attrib);

		if (offset == VertexFormat::InvalidOffset) {
			return nullptr;
		}

		return this->data + offset;
	}

	const std::uint8_t* VertexArray::getAttribPtr(const int index, const VertexAttrib::Enum attrib) const {
		return const_cast<VertexArray*>(this)->getAttribPtr(index, attrib);
	}

	void VertexArray::setAttribValue(const int index, const VertexAttrib::Enum attrib, const void *attribValue) {
		std::uint8_t *attribPtr = this->getAttribPtr(index, attrib);
		assert(attribPtr);

		const int size = this->format->getAttrib(attrib).getSize();
		std::memcpy(attribPtr, attribValue, size);
	}

	void VertexArray::getAttribValue(const int index, const VertexAttrib::Enum attrib, void *attribValue) const {
		const std::uint8_t *attribPtr = this->getAttribPtr(index, attrib);
		assert(attribPtr);

		const int size = this->format->getAttrib(attrib).getSize();
		std::memcpy(attribValue, attribPtr, size);
	}
}}
