
#include "MeshSubsetGeneratorPlane.hpp"

#include <xe/gfx/VertexArray.hpp>

namespace xe { namespace gfx {

    MeshSubsetGeneratorPlane::MeshSubsetGeneratorPlane(GraphicsDriver *driver) : MeshSubsetGenerator(driver) {}

    int MeshSubsetGeneratorPlane::getVertexBufferSize(const MeshSubsetGeneratorParams &params) const {
        assert(params.format && params.format->getSize() > 0);
        
        return params.format->getSize() * (params.slices + 1) * (params.stacks + 1);
    }

    int MeshSubsetGeneratorPlane::getIndexBufferSize(const MeshSubsetGeneratorParams &params) const {
        assert(params.iformat == IndexFormat::Index32);
        
        return 6 * IndexFormat::getSize(params.iformat) * params.slices * params.stacks;
    }

    void MeshSubsetGeneratorPlane::generateVertexBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const {
  //      assert(buffer);
  //      assert(params.format->getSize() > 0);
  //      
  //  	auto locker = buffer->getLocker();
		//
		//VertexArray array(locker.getPointer(), params.format);

  //      const float left = -0.5f;
  //      const float right = 0.5f;

		//int vertexIndex = 0;

		//// generate vertex data
  //      for (int i=0; i<params.slices + 1; i++) {
  //          float ti = static_cast<float>(i) / static_cast<float>(params.slices);

  //          for (int j=0; j<params.stacks + 1; j++) {
  //              float tj = static_cast<float>(j) / static_cast<float>(params.stacks);

		//		// generate position
  //              xe::Vector4f position (
  //                  xe::lerp(-0.5f, 0.5f, tj),
  //                  xe::lerp(0.5f, -0.5f, ti),
  //                  0.0f, 1.0f    
  //              );
		//		array.setValue(vertexIndex, VertexAttrib::Position, position);

		//		// generate normal
		//		if (params.format->hasAttrib(VertexAttrib::Normal)) {
		//			xe::Vector4f normal = {0.0f, 0.0f, -1.0f, 0.0f};
		//			array.setValue(vertexIndex, VertexAttrib::Normal, normal);
		//		}

		//		// generate texture coords
		//		if (params.format->hasAttrib(VertexAttrib::TexCoord)) {
		//			xe::Vector4f tex_coord (
		//				xe::lerp( 0.0f, 1.0f, tj),
		//				xe::lerp( 1.0f, 0.0f, ti),
		//				0.0f, 1.0f    
		//			);

		//			array.setValue(vertexIndex, VertexAttrib::TexCoord, tex_coord);
		//		}

		//		vertexIndex++;
  //          }
  //      }
		////ewzzzzzzzz
    }

    void MeshSubsetGeneratorPlane::generateIndexBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const {
        assert(buffer);
        assert(params.iformat == IndexFormat::Index32);

		std::vector<int> indices;

		for (int i=0; i<params.slices; i++) {
			for (int j=0; j<params.stacks; j++) {
				const int p0 = (i + 0) + (j + 0) * (params.slices + 1);
				const int p1 = (i + 1) + (j + 0) * (params.slices + 1);
				const int p2 = (i + 0) + (j + 1) * (params.slices + 1);
				const int p3 = (i + 1) + (j + 1) * (params.slices + 1);

				indices.push_back(p0);
				indices.push_back(p1);
				indices.push_back(p2);

				indices.push_back(p1);
				indices.push_back(p3);
				indices.push_back(p2);
			}
		}

		buffer->write(indices.data());
    }
}}
