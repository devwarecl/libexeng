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

	GraphicsDriver::~GraphicsDriver() {}
    
	xe::gfx::MeshSubsetPtr GraphicsDriver::createMeshSubset(BufferPtr vertexBuffer, const VertexFormat *format) {
		std::vector<BufferPtr> vertexBuffers;

		vertexBuffers.push_back(std::move(vertexBuffer));

		BufferPtr ibuffer;
		return this->createMeshSubset (
			std::move(vertexBuffers), 
			format, 
			std::move(ibuffer), 
			IndexFormat::Unknown
		);

	}

	xe::gfx::MeshSubsetPtr GraphicsDriver::createMeshSubset(BufferPtr vertexBuffer, const VertexFormat *format, BufferPtr ibuffer, IndexFormat::Enum iformat) {
		std::vector<BufferPtr> vertexBuffers;

		vertexBuffers.push_back(std::move(vertexBuffer));

		return this->createMeshSubset(std::move(vertexBuffers), format, std::move(ibuffer), iformat);
	}

	xe::gfx::MeshSubsetPtr GraphicsDriver::createMeshSubset(std::vector<BufferPtr> vbuffers, const VertexFormat *vformat) {
		BufferPtr ibuffer;
		return this->createMeshSubset(std::move(vbuffers), vformat, std::move(ibuffer), IndexFormat::Unknown);
	}

	Material2Ptr GraphicsDriver::createMaterial(const MaterialFormat2 * /*format*/) {
        return Material2Ptr();
    }

    TexturePtr GraphicsDriver::createTexture(const Image *image) {
        assert(image);

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
	}

	void GraphicsDriver::render(const xe::gfx::Mesh *mesh) {
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
