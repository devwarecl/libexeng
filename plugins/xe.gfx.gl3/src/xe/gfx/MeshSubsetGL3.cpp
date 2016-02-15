
#include "MeshSubsetGL3.hpp"
#include "BufferGL3.hpp"
#include "UtilGL3.hpp"
#include "DebugGL3.hpp"

namespace xe { namespace gfx { namespace gl3 {

	const std::string errMessage = "MeshSubsetGL3::MeshSubsetGL3 -> The vertex buffer vector must contain at least one element.";
	
    MeshSubsetGL3::MeshSubsetGL3(std::vector<BufferPtr> vertexBuffers, const VertexFormat &format) {
#if defined(EXENG_DEBUG)
        if (vertexBuffers.size() == 0) {
            throw std::runtime_error(errMessage);
        }
#endif
		this->initializeVertexArray(std::move(vertexBuffers), format);
		this->construct();
    }

	MeshSubsetGL3::MeshSubsetGL3(std::vector<BufferPtr> vertexBuffers, const VertexFormat &format, BufferPtr indexBuffer, IndexFormat::Enum indexFormat) {
#if defined(EXENG_DEBUG)
        if (vertexBuffers.size() == 0) {
            throw std::runtime_error(errMessage);
        }
#endif
		this->initializeVertexArray(std::move(vertexBuffers), format);
		this->initializeIndexArray(std::move(indexBuffer), indexFormat);
		this->construct();
	}

	void MeshSubsetGL3::initializeVertexArray(std::vector<BufferPtr> vertexBuffers, const VertexFormat &format) {
		assert(this);

		for (auto &vbuffer : vertexBuffers) {
			BufferPtr _buffer = std::move(vbuffer);

			std::unique_ptr<BufferGL3> buffer(static_cast<BufferGL3*>(_buffer.release()));
			this->buffers.push_back(std::move(buffer));
		}

		this->vertexFormat = format;
	}

	void MeshSubsetGL3::initializeIndexArray(BufferPtr indexBuffer, IndexFormat::Enum indexFormat) {
		assert(this);

		BufferPtr buffer = std::move(indexBuffer);

		this->indexBuffer.reset(static_cast<BufferGL3*>(buffer.release()));
		this->indexFormat = indexFormat;
	}

	void MeshSubsetGL3::construct() {
		assert(this);

		const VertexFormat format = this->getFormat();

		const bool multiBuffer = (this->buffers.size() > 1);

		::glGenVertexArrays(1, &this->vertexArrayId);
        ::glBindVertexArray(this->vertexArrayId);

		if (!multiBuffer) {
			int baseAttrib = 0;
			int offset = 0;

			const auto buffer = static_cast<BufferGL3*>(this->getBuffer(0));
			const GLenum bufferTarget = buffer->getTarget();
			const GLuint bufferId = buffer->getBufferId();

			::glBindBuffer(bufferTarget, bufferId);

			for (const VertexField& field : format.fields) {
				if (field.attribute == VertexAttrib::Unused) {
					break;
				}
				
				const DataType::Enum dataTypeKey = field.dataType;
				const GLenum dataType = convDataType(dataTypeKey);
				const void *data = reinterpret_cast<const void*>(offset);

				::glEnableVertexAttribArray(baseAttrib);
				::glVertexAttribPointer(baseAttrib, field.count, dataType, GL_FALSE, format.getSize(), data);
            
				offset += field.count * DataType::getSize(dataTypeKey);
				++baseAttrib;
			}

			GL3_CHECK();
		} else {
			int baseAttrib = 0;

			for (const VertexField& field : format.fields) {
				if (field.attribute == VertexAttrib::Unused) {
					break;
				}
				
				const auto buffer = static_cast<BufferGL3*>(this->getBuffer(baseAttrib));
				const GLenum bufferTarget = buffer->getTarget();
				const GLuint bufferId = buffer->getBufferId();

				::glBindBuffer(bufferTarget, bufferId);

				const DataType::Enum dataTypeKey = field.dataType;
				const GLenum dataType = convDataType(dataTypeKey);
				
				::glEnableVertexAttribArray(baseAttrib);
				::glVertexAttribPointer(baseAttrib, field.count, dataType, GL_FALSE, 0, nullptr);
				
				++baseAttrib;
			}

			GL3_CHECK();
		}

		if (this->indexBuffer) {
			const auto buffer = static_cast<const BufferGL3*>(this->indexBuffer.get());
			const GLuint bufferId = buffer->getBufferId();
			const GLenum target = buffer->getTarget();

			::glBindBuffer(target, bufferId);

			GL3_CHECK();
		}

		::glBindVertexArray(0);
		::glBindBuffer(GL_ARRAY_BUFFER, 0);
		::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		GL3_CHECK();

#if defined(EXENG_DEBUG)
		::glBindVertexArray(this->vertexArrayId);
		xe::gfx::gl3::checkMeshSubsetBinding(this);
		::glBindVertexArray(0);
		::glBindBuffer(GL_ARRAY_BUFFER, 0);
		::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
		GL3_CHECK();
	}
	
    MeshSubsetGL3::~MeshSubsetGL3() {
		assert(this);
		assert(this->vertexArrayId);

		::glDeleteVertexArrays(1, &this->vertexArrayId);
    }

    TypeInfo MeshSubsetGL3::getTypeInfo() const {
		assert(this);

        return TypeId<MeshSubsetGL3>();
    }
}}}
