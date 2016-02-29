
#include "MeshSubsetGeneratorPlane.hpp"

#include <xe/gfx/VertexArray.hpp>

namespace xe { namespace gfx {

    MeshSubsetGeneratorPlane::MeshSubsetGeneratorPlane(GraphicsDriver *driver) : MeshSubsetGenerator(driver) {}

    int MeshSubsetGeneratorPlane::getVertexBufferSize(const MeshSubsetGeneratorParams &params) const {
        assert(params.format && params.format->getSize() > 0);
        assert(params.slices == 1);
        assert(params.stacks == 1);

        return 4 * params.format->getSize();
    }

    int MeshSubsetGeneratorPlane::getIndexBufferSize(const MeshSubsetGeneratorParams &params) const {
        assert(params.iformat == IndexFormat::Index32);
        assert(params.slices == 1);
        assert(params.stacks == 1);

        return 6 * IndexFormat::getSize(params.iformat);
    }

    void MeshSubsetGeneratorPlane::generateVertexBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const {
        assert(buffer);
        assert(params.format->getSize() > 0);
        assert(params.slices == 1);
        assert(params.stacks == 1);

    	auto locker = buffer->getLocker();
		
		VertexArray array(locker.getPointer(), params.format);

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

    void MeshSubsetGeneratorPlane::generateIndexBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const {
        assert(buffer);
        assert(params.iformat == IndexFormat::Index32);
        assert(params.slices == 1);
        assert(params.stacks == 1);

        int indices[] = {
			0 + 0,  0 + 1,  0 + 2,      
			0 + 1,  0 + 3,  0 + 2
		};

		buffer->write(indices);    
    }
}}
