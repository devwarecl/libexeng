
#include "MeshSubsetGeneratorBox.hpp"

#include <xe/gfx/VertexArray.hpp>

namespace xe { namespace gfx {
    static const int BOX_TRIANGLE_PER_FACE_COUNT = 2;
	static const int BOX_FACE_COUNT = 6;
	static const int BOX_VERTEX_PER_FACE_COUNT = 4;
	static const int BOX_VERTEX_COUNT = BOX_FACE_COUNT * BOX_VERTEX_PER_FACE_COUNT;

    //! TODO: Replace with a quaternion object
    struct Rotation {
		float angle = 0.0f;
		Vector3f axis = {0.0f, 0.0f, 0.0f};

		Rotation() {}
		Rotation(float angle_, const Vector3f &axis_) : angle(angle_), axis(axis_) {}
	};

    MeshSubsetGeneratorBox::MeshSubsetGeneratorBox(GraphicsDriver *driver) : MeshSubsetGenerator(driver) {}

    MeshSubsetGeneratorBox::~MeshSubsetGeneratorBox() {}

    int MeshSubsetGeneratorBox::getBufferSize(const MeshSubsetGeneratorParams &params) const {
        return BOX_VERTEX_COUNT * params.format->getSize();
    }

    int MeshSubsetGeneratorBox::getIBufferSize(const MeshSubsetGeneratorParams &params) const {
        return 3 * BOX_TRIANGLE_PER_FACE_COUNT * BOX_FACE_COUNT * IndexFormat::getSize(params.iformat);
    }

    void MeshSubsetGeneratorBox::fillBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const {
        assert(buffer);
        assert(params.format && params.format->getSize() > 0);
        assert(params.slices == 1);
        assert(params.stacks == 1);

        auto locker = buffer->getLocker(BufferUsage::Write);

		VertexArray array(locker.getPointer(), params.format);

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
		
		for (int i=0; i<BOX_FACE_COUNT; i++) {
            const float angle = rotation[i].angle;
            const auto axis = rotation[i].axis;

			Matrix4f rotationMatrix = rotate(angle, axis);

			for (int j=0; j<BOX_VERTEX_PER_FACE_COUNT; j++) {
				
				Vector4f vertexPosition = transform(rotationMatrix, position[j]);
				Vector4f vertexNormal	= transform(rotationMatrix, normal);

				const int vertexIndex = i*BOX_VERTEX_PER_FACE_COUNT + j;

				array.setValue(vertexIndex, VertexAttrib::Position, vertexPosition);
				array.setValue(vertexIndex, VertexAttrib::Normal, vertexNormal);
				array.setValue(vertexIndex, VertexAttrib::TexCoord, texCoord[j]);
			}
		}
    }

    void MeshSubsetGeneratorBox::fillIBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const {
        assert(buffer);
        assert(params.iformat == IndexFormat::Index32);
        assert(params.slices == 1);
        assert(params.stacks == 1);

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
}}
