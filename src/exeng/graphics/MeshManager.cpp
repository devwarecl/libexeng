/**
 * @file MeshManager.cpp
 * @brief MeshManager class, and private attributes implementation.
 * @todo Implement a resource management on the MeshManager class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "MeshManager.hpp"

#include <map>
#include <memory>
#include <list>
#include <functional>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <exeng/Vector.hpp>
#include <exeng/ProductManagerImpl.hpp>
#include <exeng/graphics/MeshSubsetGenerator.hpp>
#include <exeng/graphics/MeshSubsetTransformer.hpp>
#include <exeng/graphics/MeshLoader.hpp>
#include <exeng/graphics/Mesh.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>

namespace fs = boost::filesystem;

namespace exeng { namespace graphics {
	
    struct MeshManager::Private {
		ProductManagerImpl<MeshLoader, Mesh> manager;

		Mesh* storeMesh(const std::string &id, MeshPtr mesh) {
			Mesh* meshPtr = mesh.get();

			this->manager.putProduct(id, std::move(mesh));

			return meshPtr;
		}

		template<typename Generator>
		MeshPtr generateMesh(GraphicsDriver *driver, const VertexFormat* vformat, const IndexFormat::Enum iformat, const Matrix4f &transformation) {
			Generator generator;
			MeshSubsetTransformer transformer;

			const int vsize = generator.getVertexBufferSize(vformat);
			const int isize = generator.getIndexBufferSize(iformat);

			auto vbuffer = driver->createVertexBuffer(vsize, nullptr);
			auto ibuffer = driver->createIndexBuffer(isize, nullptr);
			auto subset = driver->createMeshSubset(std::move(vbuffer), std::move(ibuffer), *vformat);

			generator.generate(subset.get());
			transformer.transform(subset.get(), transformation);

			return std::make_unique<Mesh>(std::move(subset));
		}
    };
    
    MeshManager::MeshManager() {
        this->impl = new MeshManager::Private();
    }
    
    MeshManager::~MeshManager() {
        delete impl;
    }
    
    void MeshManager::addMeshLoader(MeshLoader *loader) {
		assert(this->impl != nullptr);

        this->impl->manager.addLoader(loader);
    }
    
    void MeshManager::removeMeshLoader(MeshLoader *loader) {
		assert(this->impl != nullptr);

        this->impl->manager.removeLoader(loader);
    }
    
    Mesh* MeshManager::getMesh(const std::string &filename) {
		assert(this->impl != nullptr);

		return this->impl->manager.getProduct(filename);
    }

	Mesh* MeshManager::generateBoxMesh(const std::string &id, GraphicsDriver *driver, const VertexFormat *vertexFormat, IndexFormat::Enum indexFormat, const Vector3f &center, const Vector3f &size) {
		assert(this->impl != nullptr);

#if defined(EXENG_DEBUG)
		if (this->impl->manager.existProduct(id)) {
			throw std::runtime_error("The mesh id '" + id + "' is already used.");
		}
#endif	
		Matrix4f transformation = scale<float, 4>(size) * translate<float>(center);

		MeshPtr mesh = this->impl->generateMesh<BoxGenerator>(driver, vertexFormat, indexFormat, transformation);

		return this->impl->storeMesh(id, std::move(mesh));
	}
	
    Mesh* MeshManager::generateScreenMesh(const std::string &id, GraphicsDriver *driver, const VertexFormat *vertexFormat, IndexFormat::Enum indexFormat) {
        assert(this->impl != nullptr);

#if defined(EXENG_DEBUG)
		if (this->impl->manager.existProduct(id)) {
			throw std::runtime_error("The mesh id '" + id + "' is already used.");
		}
#endif	

		Matrix4f transformation = translate<float>({0.5f, 0.5f, 0.0f});

		MeshPtr mesh = this->impl->generateMesh<RectGenerator>(driver, vertexFormat, indexFormat, transformation);

		return this->impl->storeMesh(id, std::move(mesh));
    }
}}
