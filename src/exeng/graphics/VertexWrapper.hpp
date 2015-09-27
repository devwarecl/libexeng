
#ifndef __EXENG_GRAPHICS_VERTEXWRAPPER_HPP__
#define __EXENG_GRAPHICS_VERTEXWRAPPER_HPP__

#include <cassert>
#include <cstdint>
#include <vector>
#include <memory>
#include <exeng/Exception.hpp>
#include <exeng/HeapBuffer.hpp>
#include <exeng/HeapBuffer.hpp>
#include <exeng/graphics/VertexFormat.hpp>

namespace exeng { namespace graphics {

	/*
	class VertexWrapper {
	public:
		VertexWrapper(const VertexFormat &vertexFormat, void* buffer, const int bufferSize)
			: vertexCount(bufferSize / vertexFormat.getSize())
		{
			assert(bufferSize % format.getSize() == 0);
			assert(buffer);

			// TODO: Validate supplied VertexType using template metaprogramming
			this->vertices = reinterpret_cast<std::uint8_t*>(buffer);
		}

		const int getVertexCount() const {
			return this->vertexCount;
		}

		template<typename Type, int Size>
		void setAttributeValue(const int index, VertexAttrib::Enum attrib, const Vector<Type, Size> &value) {
			assert(this->format.getAttrib(attrib).count == Size);
			assert(this->format.getAttrib(attrib).dataType == DataTypeTraits<Type>::Enum);

			const int offset = this->getOffset(index, attrib);
			const int size = this->format.getAttrib(attrib).getSize();

			std::memcpy(this->vertices + offset, attribValue, size);
		}
		

		void setAttributeValue(const int index, VertexAttrib::Enum attrib, const int fieldIndex, double value) {
			const int offset = this->getOffset(index, attrib);

			const int size = this->format.getAttrib(attrib).getSize();

			std::memcpy(this->vertices + offset, attribValue, size);
		}

		template<typename Type, int Size>
		Vector<Type, Size> getAttributeValue(const int index, VertexAttrib::Enum attrib) const {

		}

	private:
		const int getOffset(const int index, VertexAttrib::Enum attrib, const int fieldIndex) {
			return index * this->format.getSize() + this->format.getAttribOffset(attrib) + ;
		}

	private:
		VertexFormat format;
		const int vertexCount;
		std::uint8_t *vertices = nullptr;
	};
	*/

	template<typename VertexType>
	class TVertexWrapper {
	public:
		TVertexWrapper(const VertexFormat &vertexFormat, void* buffer, const int bufferSize)
			: vertexCount(bufferSize / vertexFormat.getSize())
		{
			assert(sizeof(VertexType) == vertexFormat.getSize());
			assert(bufferSize % vertexFormat.getSize() == 0);
			assert(buffer);

			// TODO: Validate supplied VertexType using template metaprogramming
			this->vertices = reinterpret_cast<VertexType*>(buffer);
			this->format = vertexFormat;
		}

		const int getVertexCount() const {
			return this->vertexCount;
		}

		VertexType& operator[] (const int index) {
			assert(index >= 0);
			assert(index < this->getVertexCount());

			return this->vertices[index];
		}

		const VertexType& operator[] (const int index) const {
			assert(index >= 0);
			assert(index < this->getVertexCount());

			return this->vertices[index];
		}

	private:
		VertexFormat format;
		const int vertexCount;
		VertexType *vertices = nullptr;
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
		BoxGeometryGenerator(const Vector4f &displace, const Vector3f &size) {
			this->center = center;
			this->size = size;
		}

		virtual HeapBufferPtr generateVertexBuffer(const VertexFormat &format) override {
			assert(format == Vertex::format());

			const int VERTEX_COUNT = 24;

			auto buffer = std::make_unique<HeapBuffer>(VERTEX_COUNT * Vertex::format().getSize());

			TVertexWrapper<Vertex> vertices(Vertex::format(), buffer->getPointer(), buffer->getSize());

			vertices[0] = {{-0.5f,   0.5f, -0.5f, 1.0f},   {0.0f, 0.0f, -1.0f, 0.0f},  {0.0f, 1.0f}};
			vertices[1] = {{ 0.5f,   0.5f, -0.5f, 1.0f},   {0.0f, 0.0f, -1.0f, 0.0f},  {1.0f, 1.0f}};
			vertices[2] = {{-0.5f,  -0.5f, -0.5f, 1.0f},   {0.0f, 0.0f, -1.0f, 0.0f},  {0.0f, 0.0f}};
			vertices[3] = {{ 0.5f,  -0.5f, -0.5f, 1.0f},   {0.0f, 0.0f, -1.0f, 0.0f},  {1.0f, 0.0f}};
            
			// Right face
			vertices[4] = {{0.5f,   0.5f, -0.5f, 1.0f},   {1.0f, 0.0f, 0.0f, 0.0f},   {0.0f, 1.0f}};
			vertices[5] = {{0.5f,   0.5f,  0.5f, 1.0f},   {1.0f, 0.0f, 0.0f, 0.0f},   {1.0f, 1.0f}};
			vertices[6] = {{0.5f,  -0.5f, -0.5f, 1.0f},   {1.0f, 0.0f, 0.0f, 0.0f},   {0.0f, 0.0f}};
			vertices[7] = {{0.5f,  -0.5f,  0.5f, 1.0f},   {1.0f, 0.0f, 0.0f, 0.0f},   {1.0f, 0.0f}};
            
			// Front Face
			vertices[8] = {{ 0.5f,   0.5f,  0.5f, 1.0f},   {0.0f, 0.0f, 1.0f, 0.0f},   {1.0f, 1.0f}};
			vertices[9] = {{-0.5f,   0.5f,  0.5f, 1.0f},   {0.0f, 0.0f, 1.0f, 0.0f},   {0.0f, 1.0f}};
			vertices[10] = {{ 0.5f,  -0.5f,  0.5f, 1.0f},   {0.0f, 0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}};
			vertices[11] = {{-0.5f,  -0.5f,  0.5f, 1.0f},   {0.0f, 0.0f, 1.0f, 0.0f},   {0.0f, 0.0f}};
            
			// Left face
			vertices[12] = {{-0.5f,   0.5f,  0.5f, 1.0f},  {-1.0f, 0.0f, 0.0f, 0.0f},   {1.0f, 1.0f}};
			vertices[13] = {{-0.5f,   0.5f, -0.5f, 1.0f},  {-1.0f, 0.0f, 0.0f, 0.0f},   {0.0f, 1.0f}};
			vertices[14] = {{-0.5f,  -0.5f,  0.5f, 1.0f},  {-1.0f, 0.0f, 0.0f, 0.0f},   {1.0f, 0.0f}};
			vertices[15] = {{-0.5f,  -0.5f, -0.5f, 1.0f},  {-1.0f, 0.0f, 0.0f, 0.0f},   {0.0f, 0.0f}};
            
			// Top face
			vertices[16] = {{-0.5f,   0.5f,   0.5f, 1.0f},  {0.0f, 1.0f, 0.0f, 0.0f},   {0.0f, 1.0f}};
			vertices[17] = {{ 0.5f,   0.5f,   0.5f, 1.0f},  {0.0f, 1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}};
			vertices[18] = {{-0.5f,   0.5f,  -0.5f, 1.0f},  {0.0f, 1.0f, 0.0f, 0.0f},   {0.0f, 0.0f}};
			vertices[19] = {{ 0.5f,   0.5f,  -0.5f, 1.0f},  {0.0f, 1.0f, 0.0f, 0.0f},   {1.0f, 0.0f}};
            
			// Bottom face
			vertices[20] = {{ 0.5f,  -0.5f,   0.5f, 1.0f},  {0.0f, -1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}};
			vertices[21] = {{-0.5f,  -0.5f,   0.5f, 1.0f},  {0.0f, -1.0f, 0.0f, 0.0f},   {0.0f, 1.0f}};
			vertices[22] = {{ 0.5f,  -0.5f,  -0.5f, 1.0f},  {0.0f, -1.0f, 0.0f, 0.0f},   {1.0f, 0.0f}};
			vertices[23] = {{-0.5f,  -0.5f,  -0.5f, 1.0f},  {0.0f, -1.0f, 0.0f, 0.0f},   {0.0f, 0.0f}};

			const float *values1 = (const float *) buffer->getPointer();

			;

			// Correct
			for (int i=0; i<vertices.getVertexCount(); ++i) {
				vertices[i].coord = vertices[i].coord * this->size + this->center;
			}

			return buffer;
		}

		virtual HeapBufferPtr generateIndexBuffer() override {
			int indices[] = {
				0 + 0,  0 + 1,  0 + 2,      0 + 1,  0 + 3,  0 + 2,
				4 + 0,  4 + 1,  4 + 2,      4 + 1,  4 + 3,  4 + 2, 
				8 + 0,  8 + 1,  8 + 2,      8 + 1,  8 + 3,  8 + 2, 
				12 + 0, 12 + 1, 12 + 2,     12 + 1, 12 + 3, 12 + 2, 
				16 + 0, 16 + 1, 16 + 2,     16 + 1, 16 + 3, 16 + 2, 
				20 + 0, 20 + 1, 20 + 2,     20 + 1, 20 + 3, 20 + 2
			};

			HeapBufferPtr buffer(new HeapBuffer(sizeof(indices)));
			buffer->setData(indices);

			return buffer;
		}

	private:
		Vector4f center;
		Vector4f size;
	};
}}

#endif	// __EXENG_GRAPHICS_VERTEXWRAPPER_HPP__
