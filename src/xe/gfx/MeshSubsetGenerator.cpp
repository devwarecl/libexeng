
#include "MeshSubsetGenerator.hpp"

#include "VertexArray.hpp"
#include "MeshSubset.hpp"

#include <xe/Vector.hpp>
#include <xe/Matrix.hpp>
#include <xe/HeapBuffer.hpp>

namespace xe { namespace gfx {

	// TODO: Replace with a Quaternion
	struct Rotation {
		float angle = 0.0f;
		Vector3f axis = {0.0f, 0.0f, 0.0f};

		Rotation() {}
		Rotation(float angle_, const Vector3f &axis_) : angle(angle_), axis(axis_) {}
	};

	const int BOX_TRIANGLE_PER_FACE_COUNT = 2;
	const int BOX_FACE_COUNT = 6;
	const int BOX_VERTEX_PER_FACE_COUNT = 4;
	const int BOX_VERTEX_COUNT = BOX_FACE_COUNT * BOX_VERTEX_PER_FACE_COUNT;

	// Generate raw vertex format.
	// Only supports float32 datatype for now.
	void BoxGenerator::fillVertexBuffer(Buffer *buffer, const VertexFormat *format) {
		auto tempBuffer = std::make_unique<HeapBuffer>(buffer->getSize());
		auto locker = tempBuffer->getLocker<void>();

		VertexArray array(locker.getPointer(), format);

		// Generate primary square
		Vector4f position[] = {
			{ 0.5f,   0.5f,  0.5f, 1.0f}, 
			{-0.5f,   0.5f,  0.5f, 1.0f}, 
			{ 0.5f,  -0.5f,  0.5f, 1.0f}, 
			{-0.5f,  -0.5f,  0.5f, 1.0f} 
		};

		Vector4f normal = {0.0f,  0.0f,  1.0f,  0.0};

		Vector4f texCoord[] = {
			{0.0f, 1.0f, 0.0f, 1.0},
			{1.0f, 1.0f, 0.0f, 1.0},
			{0.0f, 0.0f, 0.0f, 1.0},
			{1.0f, 0.0f, 0.0f, 1.0}
		};

		for (int i=0; i<4; i++) {
			array.setValue(i, VertexAttrib::Position, position[i]);
			array.setValue(i, VertexAttrib::Normal, normal);
			array.setValue(i, VertexAttrib::TexCoord, texCoord[i]);
		}

		// Generate the rest of the cube
		Rotation rotation[] = {
			{rad(  0.0f), {0.0f, 1.0f, 0.0}},
			{rad( 90.0f), {0.0f, 1.0f, 0.0}},
			{rad(180.0f), {0.0f, 1.0f, 0.0}},
			{rad(270.0f), {0.0f, 1.0f, 0.0}},

			{rad( 90.0f), {1.0f, 0.0f, 0.0}},
			{rad(-90.0f), {1.0f, 0.0f, 0.0}}
		};
		
		for (int i=1; i<BOX_FACE_COUNT; i++) {
			Matrix4f rotationMatrix = rotate(rotation[i].angle, rotation[i].axis);

			for (int j=0; j<BOX_VERTEX_PER_FACE_COUNT; j++) {
				
				Vector4f vertexPosition = transform(rotationMatrix, position[i]);
				Vector4f vertexNormal	= transform(rotationMatrix, normal);

				const int vertexIndex = i*BOX_VERTEX_PER_FACE_COUNT + j;

				array.setValue(vertexIndex, VertexAttrib::Position, vertexPosition);
				array.setValue(vertexIndex, VertexAttrib::Normal, vertexNormal);
				array.setValue(vertexIndex, VertexAttrib::TexCoord, texCoord[j]);
			}
		}

		buffer->write(locker.getPointer());
	}
	
	void BoxGenerator::fillIndexBuffer(Buffer *buffer, IndexFormat::Enum indexFormat) {
		int indices[] = {
			0 + 0,  0 + 1,  0 + 2,      0 + 1,  0 + 3,  0 + 2,
			4 + 0,  4 + 1,  4 + 2,      4 + 1,  4 + 3,  4 + 2, 
			8 + 0,  8 + 1,  8 + 2,      8 + 1,  8 + 3,  8 + 2, 
			12 + 0, 12 + 1, 12 + 2,     12 + 1, 12 + 3, 12 + 2, 
			16 + 0, 16 + 1, 16 + 2,     16 + 1, 16 + 3, 16 + 2, 
			20 + 0, 20 + 1, 20 + 2,     20 + 1, 20 + 3, 20 + 2
		};

		buffer->write(indices);
	}

	int BoxGenerator::getVertexBufferSize(const VertexFormat *format) const {
		return BOX_VERTEX_COUNT * format->getSize();
	}

	int BoxGenerator::getIndexBufferSize(const IndexFormat::Enum format) const {
		return 3 * BOX_TRIANGLE_PER_FACE_COUNT * BOX_FACE_COUNT * IndexFormat::getSize(format);
	}

	void BoxGenerator::generate(MeshSubset *subset) {
		const VertexFormat format = subset->getFormat();

		this->fillVertexBuffer(subset->getBuffer(0), &format);
		this->fillIndexBuffer(subset->getIndexBuffer(), subset->getIndexFormat());
	}
}}


namespace xe { namespace gfx {

	int RectGenerator::getVertexBufferSize(const VertexFormat *format) const {
		return 4 * format->getSize();
	}

	int RectGenerator::getIndexBufferSize(const IndexFormat::Enum format) const {
		return 6 * IndexFormat::getSize(format);
	}

	void RectGenerator::fillVertices(Buffer *buffer, const VertexFormat *format) {
		auto locker = buffer->getLocker<void>();
		
		VertexArray array(locker.getPointer(), format);

		Vector4f position[] = {
			{ 0.5f,   0.5f,  0.5f, 1.0f}, 
			{-0.5f,   0.5f,  0.5f, 1.0f}, 
			{ 0.5f,  -0.5f,  0.5f, 1.0f}, 
			{-0.5f,  -0.5f,  0.5f, 1.0f} 
		};

		Vector4f texCoord[] = {
			{0.0f, 1.0f, 0.0f, 1.0},
			{1.0f, 1.0f, 0.0f, 1.0},
			{0.0f, 0.0f, 0.0f, 1.0},
			{1.0f, 0.0f, 0.0f, 1.0}
		};

		for (int i=0; i<4; i++) {
			array.setValue(i, VertexAttrib::Position, position[i]);
			array.setValue(i, VertexAttrib::TexCoord, texCoord[i]);
		}
	}
	
	void RectGenerator::fillIndices(Buffer *buffer, IndexFormat::Enum indexFormat) {
		int indices[] = {
			0 + 0,  0 + 1,  0 + 2,      
			0 + 1,  0 + 3,  0 + 2
		};

		buffer->write(indices);
	}

	void RectGenerator::generate(MeshSubset *subset) {
		const VertexFormat format = subset->getFormat();

		this->fillVertices(subset->getBuffer(0), &format);
		this->fillIndices(subset->getIndexBuffer(), subset->getIndexFormat());
	}
}}
