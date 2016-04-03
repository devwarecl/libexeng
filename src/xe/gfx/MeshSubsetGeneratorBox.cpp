
#include "MeshSubsetGeneratorBox.hpp"

#include <xe/gfx/VertexArray.hpp>

namespace xe { namespace gfx {

	/**
	 * @brief Display the supplied buffer data as vertices to stantard output.
	 */
	void displayVertexData(const VertexFormat *format, const void* buffer, const int buffer_size) {
		assert(format);
		assert(buffer);

		const char *data = (const char*)buffer;
		int offset = 0;
		int vertexIndex = 0;

		const int VERTEX_STRIDE = format->getSize();
		const int VERTEX_COUNT = buffer_size / VERTEX_STRIDE;

		while (offset < buffer_size) {
			std::cout << "V " << ++vertexIndex;

			for (int i=0; i<VertexFormat::FieldCount; i++) {
				const VertexField *field = &format->fields[i];

				if (field->attribute == VertexAttrib::Unused) {
					break;
				}
			
				switch (field->count) {
				case 1:	std::cout << "(" <<  *(const float*)(&data[offset]) << "), ";
				case 2:	std::cout << "(" <<  xe::Vector2f((const float*)(&data[offset])) << "), ";
				case 3:	std::cout << "(" <<  xe::Vector3f((const float*)(&data[offset])) << "), ";
				case 4:	std::cout << "(" <<  xe::Vector4f((const float*)(&data[offset])) << "), ";
				}

				offset += field->getSize();
			}

			std::cout << std::endl;
		}
	}

	const int FACE_COUNT = 6;

    //! TODO: Replace with a quaternion object
    struct Rotation {
		float angle = 0.0f;
		Vector3f axis = {0.0f, 0.0f, 0.0f};

		Rotation() {}
		Rotation(float angle_, const Vector3f &axis_) : angle(angle_), axis(axis_) {}
	};

    MeshSubsetGeneratorBox::MeshSubsetGeneratorBox(GraphicsDriver *driver) : MeshSubsetGenerator(driver) {}

    MeshSubsetGeneratorBox::~MeshSubsetGeneratorBox() {}

    int MeshSubsetGeneratorBox::getVertexBufferSize(const MeshSubsetGeneratorParams &params) const {
        assert(params.format && params.format->getSize() > 0);
        
        return FACE_COUNT * params.format->getSize() * (params.slices + 1) * (params.stacks + 1);
    }

    int MeshSubsetGeneratorBox::getIndexBufferSize(const MeshSubsetGeneratorParams &params) const {
        assert(params.iformat == IndexFormat::Index32);
        
        return FACE_COUNT * 6 * IndexFormat::getSize(params.iformat) * params.slices * params.stacks;
    }

    void MeshSubsetGeneratorBox::generateVertexBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const {
        assert(buffer);
        assert(params.format && params.format->getSize() > 0);

		const int POINTS_PER_FACE_COUNT = (params.slices + 1)*(params.stacks + 1);

    	auto locker = buffer->getLocker();
		
		VertexArray array(locker.getPointer(), params.format);

        const float left = -0.5f;
        const float right = 0.5f;

		// generate primary vertex data
		std::vector<xe::Vector4f> positions;
		std::vector<xe::Vector4f> normals;
		std::vector<xe::Vector4f> texCoords;

        for (int i=0; i<params.slices + 1; i++) {
            float ti = static_cast<float>(i) / static_cast<float>(params.slices);

            for (int j=0; j<params.stacks + 1; j++) {
                float tj = static_cast<float>(j) / static_cast<float>(params.stacks);

				// generate position
				xe::Vector4f position (
                    xe::lerp(-0.5f, 0.5f, tj),
                    xe::lerp(0.5f, -0.5f, ti),
                    -0.5f, 1.0f    
                );

				positions.push_back(position);
                
				// generate normal
				if (params.format->hasAttrib(VertexAttrib::Normal)) {
					normals.push_back(xe::Vector4f(0.0f, 0.0f, -1.0f, 0.0f));
				}

				// generate texture coords
				if (params.format->hasAttrib(VertexAttrib::TexCoord)) {
					xe::Vector4f texCoord (
						xe::lerp( 0.0f, 1.0f, tj),
						xe::lerp( 1.0f, 0.0f, ti),
						0.0f, 1.0f    
					);

					texCoords.push_back(texCoord);
				}

				// TODO: generate remaining vertex attributes.
            }
        }
		
		struct Rotation {
			float angle;
			Vector3f axis;
		};

		// Generate the rest of the cube using the first face
		Rotation rotation[] = {
			{rad(  0.0f), {0.0f, 1.0f, 0.0}},
			{rad( 90.0f), {0.0f, 1.0f, 0.0}},
			{rad(180.0f), {0.0f, 1.0f, 0.0}},
			{rad(270.0f), {0.0f, 1.0f, 0.0}},

			{rad( 90.0f), {1.0f, 0.0f, 0.0}},
			{rad(-90.0f), {1.0f, 0.0f, 0.0}}
		};
		
		for (int i=0; i<FACE_COUNT; i++) {
            const float angle = rotation[i].angle;
            const auto axis = rotation[i].axis;

			const Matrix4f rotationMatrix = rotate(angle, axis);

			for (int j=0; j<POINTS_PER_FACE_COUNT; j++) {
				
				const Vector4f vertexPosition = transform(rotationMatrix, positions[j]);
				const Vector4f vertexNormal	= transform(rotationMatrix, normals[j]);

				const int vertexIndex = i*POINTS_PER_FACE_COUNT + j;

				array.setValue(vertexIndex, VertexAttrib::Position, vertexPosition);
				array.setValue(vertexIndex, VertexAttrib::Normal, vertexNormal);
				array.setValue(vertexIndex, VertexAttrib::TexCoord, texCoords[j]);

#if defined(EXENG_DEBUG)
				xe::Vector4f testPosition, testNormal, testTexCoord;
				array.getAttribValue(vertexIndex, VertexAttrib::Position, &testPosition);
				array.getAttribValue(vertexIndex, VertexAttrib::Normal, &testNormal);
				array.getAttribValue(vertexIndex, VertexAttrib::TexCoord, &testTexCoord);

				assert(std::memcmp(&testPosition, &vertexPosition, params.format->getAttrib(VertexAttrib::Position).getSize()) == 0);
				assert(std::memcmp(&testNormal, &vertexNormal, params.format->getAttrib(VertexAttrib::Normal).getSize()) == 0);
				assert(std::memcmp(&testTexCoord, &texCoords[j], params.format->getAttrib(VertexAttrib::TexCoord).getSize()) == 0);
#endif

//#if defined(EXENG_DEBUG)
//				std::cout << "(" << vertexPosition << "), (" << vertexNormal << "), ("  << texCoords[j] << ")" << std::endl;
//#endif
			}
		}

//#if defined(EXENG_DEBUG)
//		displayVertexData(params.format, locker.getPointer(), locker.getSize());
//
//		std::cout << std::endl;
//#endif
    }

    void MeshSubsetGeneratorBox::generateIndexBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const {
        assert(buffer);
        assert(params.iformat == IndexFormat::Index32);

		std::vector<int> indices;

		int baseIndex = 0;

		for (int face=0; face<FACE_COUNT; face++) {
			for (int i=0; i<params.slices; i++) {
				for (int j=0; j<params.stacks; j++) {

					const int p0 = baseIndex + (i + 0) + (j + 0) * (params.slices + 1);
					const int p1 = baseIndex + (i + 1) + (j + 0) * (params.slices + 1);
					const int p2 = baseIndex + (i + 0) + (j + 1) * (params.slices + 1);
					const int p3 = baseIndex + (i + 1) + (j + 1) * (params.slices + 1);

#if defined (EXENG_DEBUG)
					const int VERTEX_COUNT = FACE_COUNT * (params.slices + 1) * (params.stacks + 1);

					assert(p0 >= 0 && p0 < VERTEX_COUNT);
					assert(p1 >= 0 && p1 < VERTEX_COUNT);
					assert(p2 >= 0 && p2 < VERTEX_COUNT);
					assert(p3 >= 0 && p3 < VERTEX_COUNT);
#endif
					indices.push_back(p0);
					indices.push_back(p1);
					indices.push_back(p2);

					indices.push_back(p1);
					indices.push_back(p3);
					indices.push_back(p2);
				}
			}

			baseIndex += (params.slices + 1) * (params.stacks + 1);
		}

		buffer->write(indices.data());
    }
}}
