
#ifndef __EXENG_GRAPHICS_VERTEXWRAPPER_HPP__
#define __EXENG_GRAPHICS_VERTEXWRAPPER_HPP__

#include <cstdint>
#include <vector>
#include <memory>
#include <exeng/Exception.hpp>
#include <exeng/HeapBuffer.hpp>
#include <exeng/HeapBuffer.hpp>
#include <exeng/graphics/VertexFormat.hpp>

namespace exeng { namespace graphics {
	class VertexWrapper {
	public:
		VertexWrapper(const VertexFormat &format, Buffer *buffer) {
			this->format = format;
			this->buffer = buffer;
		}

		void setVertexPosition(const int index, const Vector3f &position) {
			this->setVertexAttribute<float, 3>(index, VertexAttrib::Position, position);
		}

		void setVertexNormal(const int index, const Vector3f &normal) {
			this->setVertexAttribute<float, 3>(index, VertexAttrib::Normal, normal);
		}

		void setVertexTexCoord(const int index, const Vector2f &texCoord) {
			this->setVertexAttribute<float, 2>(index, VertexAttrib::TexCoord, texCoord);
		}

		Vector3f getVertexPosition(const int index) const {
			return this->getVertexAttribute<float, 3>(index, VertexAttrib::Position);
		}

		Vector3f getVertexNormal(const int index) const {
			return this->getVertexAttribute<float, 3>(index, VertexAttrib::Normal);
		}

		Vector2f getVertexTexCoord(const int index) const {
			return this->getVertexAttribute<float, 2>(index, VertexAttrib::TexCoord);
		}

		void setVertex(const int index, const Vector3f &position, const Vector3f &normal, const Vector2f &texCoord) {
			this->setVertexPosition(index, position);
			this->setVertexNormal(index, normal);
			this->setVertexTexCoord(index, texCoord);
		}

		template<typename Type, int Size>
		void setVertexAttribute(const int vertexIndex, const VertexAttrib::Enum attrib, const Vector<Type, Size> &value) {
//#if defined(EXENG_DEBUG)
//			if (sizeof(value) != format.getAttrib(attrib).getSize()) {
//				EXENG_THROW_EXCEPTION("Invalid vertex attribute size.");
//			}
//
//			if (DataTypeTraits<Type>::Enum != format.getAttrib(attrib).dataType) {
//				EXENG_THROW_EXCEPTION("Invalid vertex attribute data type.");
//			}
//#endif
			const int offset = this->getOffset(vertexIndex, attrib);

			this->buffer->setData(&value, sizeof(value), 0, offset);
		}

		template<typename Type, int Size>
		Vector<Type, Size> getVertexAttribute(const int vertexIndex, const VertexAttrib::Enum attrib) const {
			const int offset = this->getOffset(vertexIndex, attrib);

			Vector<Type, Size> value;
			this->buffer->getData(&value, sizeof(value), 0, offset);
			return value;
		}

	private:
		const int getOffset(const int vertexIndex, const VertexAttrib::Enum attrib) const {
			return vertexIndex * format.getSize() + format.getAttribOffset(attrib);
		}

	private:
		VertexFormat format;
		Buffer *buffer = nullptr;
	};

	class GeometryGenerator {
	public:
		virtual ~GeometryGenerator() {}

		virtual HeapBufferPtr generateVertexBuffer(const VertexFormat &format) = 0;
		virtual HeapBufferPtr generateIndexBuffer() = 0;
	};
	typedef std::unique_ptr<GeometryGenerator> GeometryGeneratorPtr;

	class BoxGeometryGenerator : public GeometryGenerator {
	public:
		BoxGeometryGenerator(const Vector3f &center, const Vector3f &size) {}

		virtual HeapBufferPtr generateVertexBuffer(const VertexFormat &format) override {
			const int vertexCount = 24;

			HeapBufferPtr buffer(new HeapBuffer(vertexCount * format.getSize()));

			VertexWrapper vertices(format, buffer.get());
			vertices.setVertex(0, {-0.5f,   0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {0.0f, 1.0f});
			vertices.setVertex(1, { 0.5f,   0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {1.0f, 1.0f});
			vertices.setVertex(2, {-0.5f,  -0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {0.0f, 0.0f});
			vertices.setVertex(3, { 0.5f,  -0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {1.0f, 0.0f});
            
			// Right face
			vertices.setVertex(4, {0.5f,   0.5f, -0.5f},   {1.0f, 0.0f, 0.0f},   {0.0f, 1.0f});
			vertices.setVertex(5, {0.5f,   0.5f,  0.5f},   {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f});
			vertices.setVertex(6, {0.5f,  -0.5f, -0.5f},   {1.0f, 0.0f, 0.0f},   {0.0f, 0.0f});
			vertices.setVertex(7, {0.5f,  -0.5f,  0.5f},   {1.0f, 0.0f, 0.0f},   {1.0f, 0.0f});
                
			// Front Face
			vertices.setVertex(8, { 0.5f,   0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {1.0f, 1.0f});
			vertices.setVertex(9, {-0.5f,   0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {0.0f, 1.0f});
			vertices.setVertex(10, { 0.5f,  -0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {1.0f, 0.0f});
			vertices.setVertex(11, {-0.5f,  -0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f});
                
			// Left face
			vertices.setVertex(12, {-0.5f,   0.5f,  0.5f},  {-1.0f, 0.0f, 0.0f},   {1.0f, 1.0f});
			vertices.setVertex(13, {-0.5f,   0.5f, -0.5f},  {-1.0f, 0.0f, 0.0f},   {0.0f, 1.0f});
			vertices.setVertex(14, {-0.5f,  -0.5f,  0.5f},  {-1.0f, 0.0f, 0.0f},   {1.0f, 0.0f});
			vertices.setVertex(15, {-0.5f,  -0.5f, -0.5f},  {-1.0f, 0.0f, 0.0f},   {0.0f, 0.0f});
                
			// Top face
			vertices.setVertex(16, {-0.5f,   0.5f,   0.5f},  {0.0f, 1.0f, 0.0f},   {0.0f, 1.0f});
			vertices.setVertex(17, { 0.5f,   0.5f,   0.5f},  {0.0f, 1.0f, 0.0f},   {1.0f, 1.0f});
			vertices.setVertex(18, {-0.5f,   0.5f,  -0.5f},  {0.0f, 1.0f, 0.0f},   {0.0f, 0.0f});
			vertices.setVertex(19, { 0.5f,   0.5f,  -0.5f},  {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f});
                
			// Bottom face
			vertices.setVertex(20, { 0.5f,  -0.5f,   0.5f},  {0.0f, -1.0f, 0.0f},   {1.0f, 1.0f});
			vertices.setVertex(21, {-0.5f,  -0.5f,   0.5f},  {0.0f, -1.0f, 0.0f},   {0.0f, 1.0f});
			vertices.setVertex(22, { 0.5f,  -0.5f,  -0.5f},  {0.0f, -1.0f, 0.0f},   {1.0f, 0.0f});
			vertices.setVertex(23, {-0.5f,  -0.5f,  -0.5f},  {0.0f, -1.0f, 0.0f},   {0.0f, 0.0f});

			// Correct
			for (int i=0; i<vertexCount; ++i) {
				Vector3f position = vertices.getVertexPosition(i);
				position = position * size + center;
				vertices.setVertexPosition(i, position);
			}

			return buffer;
		}

		virtual HeapBufferPtr generateIndexBuffer() override {
			std::vector<int> indices = {
				0 + 0,  0 + 1,  0 + 2,      0 + 1,  0 + 3,  0 + 2,
				4 + 0,  4 + 1,  4 + 2,      4 + 1,  4 + 3,  4 + 2, 
				8 + 0,  8 + 1,  8 + 2,      8 + 1,  8 + 3,  8 + 2, 
				12 + 0, 12 + 1, 12 + 2,     12 + 1, 12 + 3, 12 + 2, 
				16 + 0, 16 + 1, 16 + 2,     16 + 1, 16 + 3, 16 + 2, 
				20 + 0, 20 + 1, 20 + 2,     20 + 1, 20 + 3, 20 + 2
			};

			HeapBufferPtr buffer(new HeapBuffer(sizeof(int) * indices.size()));
			buffer->setData(indices.data());

			return buffer;
		}

	private:
		Vector3f center;
		Vector3f size;
	};
}}

#endif	// __EXENG_GRAPHICS_VERTEXWRAPPER_HPP__
