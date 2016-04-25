/**
 * @file GraphicsDriver.cpp
 * @brief Stub implementation of the graphics driver abstract class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "GraphicsDriver.hpp"

#include <xe/gfx/Mesh.hpp>

namespace xe { namespace gfx {

    
	xe::gfx::MeshSubsetPtr GraphicsDevice::createMeshSubset(Buffer::Ptr vertexBuffer, const VertexFormat *format) {
		std::vector<Buffer::Ptr> vertexBuffers;

		vertexBuffers.push_back(std::move(vertexBuffer));

		Buffer::Ptr ibuffer;
		return this->createMeshSubset (
			std::move(vertexBuffers), 
			format, 
			std::move(ibuffer), 
			IndexFormat::Unknown
		);

	}

	xe::gfx::MeshSubsetPtr GraphicsDevice::createMeshSubset(Buffer::Ptr vertexBuffer, const VertexFormat *format, Buffer::Ptr ibuffer, IndexFormat::Enum iformat) {
		return xe::gfx::MeshSubsetPtr();
        // std::vector<BufferPtr> vertexBuffers;
		// vertexBuffers.push_back(std::move(vertexBuffer));
		// return this->createMeshSubset(std::move(vertexBuffers), format, std::move(ibuffer), iformat);
	}

	xe::gfx::MeshSubsetPtr GraphicsDevice::createMeshSubset(std::vector<Buffer::Ptr> vbuffers, const VertexFormat *vformat) {

        return xe::gfx::MeshSubsetPtr();

		// BufferPtr ibuffer;
		// return this->createMeshSubset(std::move(vbuffers), vformat, std::move(ibuffer), IndexFormat::Unknown);
	}

    TexturePtr GraphicsDevice::createTexture(const Image *image) {
        assert(image);

        return TexturePtr();

        /*
		if (image->getType() == ImageType::Img2D) {
			Vector2i size = image->getSize();
                
            auto locker = image->getBuffer()->getLocker();
                
			return this->createTexture (
				size, 
				image->getFormat(), 
				locker.getPointer()
			);
		} else {
			return nullptr;
		}
        */
	}

	void GraphicsDevice::render(const xe::gfx::Mesh *mesh) {
		assert(mesh);

		for (int i=0; i<mesh->getSubsetCount(); i++) {
			const xe::gfx::MeshSubset *subset = mesh->getSubset(i);
			assert(subset);

			this->setMaterial(subset->getMaterial());
			this->setMeshSubset(subset);
			this->render(subset->getPrimitive(), 0);
		}
	}
}}
