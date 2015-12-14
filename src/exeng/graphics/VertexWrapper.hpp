
#ifndef __EXENG_GRAPHICS_VERTEXWRAPPER_HPP__
#define __EXENG_GRAPHICS_VERTEXWRAPPER_HPP__

#include <cassert>
#include <cstdint>
#include <vector>
#include <memory>
#include <exeng/Exception.hpp>
#include <exeng/HeapBuffer.hpp>
#include <exeng/HeapBuffer.hpp>
#include <exeng/graphics/Vertex.hpp>
#include <exeng/graphics/VertexFormat.hpp>

namespace exeng { namespace graphics {

	template<typename VertexType>
	class GeometryGenerator {
	public:
		virtual ~GeometryGenerator() {}

		virtual HeapBufferPtr generateVertexBuffer() = 0;
		virtual HeapBufferPtr generateIndexBuffer() = 0;
	};
	
	/**
	 * Generate the geometry data for a box 
	 */
	template<typename VertexType>
	class BoxGenerator : public GeometryGenerator<VertexType> {
	public:
		BoxGenerator(const Vector4f &displace, const Vector4f &size) {
			this->center = displace;
			this->size = size;
		}

		virtual HeapBufferPtr generateVertexBuffer() override {
			const int VERTEX_COUNT = 24;

			auto buffer = std::make_unique<HeapBuffer>(VERTEX_COUNT * VertexType::getFormat().getSize());

			typedef decltype(typename VertexType::coord) CoordType;
			typedef decltype(typename VertexType::normal) NormalType;
			typedef decltype(typename VertexType::texCoord) TexCoordType;

			// Generate primary square
			VertexType square[4];
			square[0].coord.set( 0.5f,   0.5f,  0.5f, 1.0f);
			square[1].coord.set(-0.5f,   0.5f,  0.5f, 1.0f);
			square[2].coord.set( 0.5f,  -0.5f,  0.5f, 1.0f);   
			square[3].coord.set(-0.5f,  -0.5f,  0.5f, 1.0f);   

			square[0].texCoord.set(0.0f, 1.0f, 0.0f, 1.0);
			square[1].texCoord.set(1.0f, 1.0f, 0.0f, 1.0);
			square[2].texCoord.set(0.0f, 0.0f, 0.0f, 1.0);
			square[3].texCoord.set(1.0f, 0.0f, 0.0f, 1.0);
			
			for (int i=0; i<4; i++) {
				square[i].normal.set(0.0f,  0.0f,  1.0f,  0.0);
			}

			// buffer->setData(vertices);

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
