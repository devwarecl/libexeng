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
#include <exeng/graphics/MeshLoader.hpp>
#include <exeng/graphics/Mesh.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/graphics/MeshSubsetGenerator.hpp>
#include <exeng/graphics/MeshSubsetTransformer.hpp>

#include <lwobject/lwo2.h>

namespace fs = boost::filesystem;

namespace exeng { namespace graphics {
	
    struct MeshManager::Private {
		GraphicsDriver *graphicsDriver = nullptr;

        std::list<std::unique_ptr<MeshLoader>> loaders;
        std::map<std::string, std::unique_ptr<Mesh>> meshes;

		std::string path;

		void checkMeshId(const std::string &id) {
			if (meshes.find(id) != meshes.end()) {
				throw std::runtime_error("MeshManager::generateBoxMesh: The mesh id '" + id + "' already exists.");
			}
		}

		Mesh* storeMesh(const std::string &id, MeshPtr mesh) {
			Mesh* meshPtr = mesh.get();

			this->meshes[id] =  std::move(mesh);

			return meshPtr;
		}

		template<typename Generator>
		MeshPtr generateMesh(const VertexFormat* vformat, const IndexFormat::Enum iformat, const Matrix4f &transformation) {
			Generator generator;
			MeshSubsetTransformer transformer;

			const int vsize = generator.getVertexBufferSize(vformat);
			const int isize = generator.getIndexBufferSize(iformat);

			auto vbuffer = this->graphicsDriver->createVertexBuffer(vsize, nullptr);
			auto ibuffer = this->graphicsDriver->createIndexBuffer(isize, nullptr);
			auto subset = this->graphicsDriver->createMeshSubset(std::move(vbuffer), std::move(ibuffer), *vformat);

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

        this->impl->loaders.push_front(std::unique_ptr<MeshLoader>(loader));
    }
    
    void MeshManager::removeMeshLoader(MeshLoader *loader) {
		assert(this->impl != nullptr);

        this->impl->loaders.remove(std::unique_ptr<MeshLoader>(loader));
    }
    
    Mesh* MeshManager::getMesh(const std::string &filename) {
		assert(this->impl != nullptr);

		GraphicsDriver *graphicsDriver = this->getGraphicsDriver();
        Mesh* mesh = nullptr;
        
        // search the mesh
        auto meshIterator = this->impl->meshes.find(filename);

        if (meshIterator != std::end(this->impl->meshes)) {
            return meshIterator->second.get();
        }

        fs::path path = fs::path(filename);

		if (!path.has_parent_path()) {
			path = fs::path(this->getPath() + "/" + filename);
		}

		if (!fs::is_regular_file(path) || !fs::exists(path)) {
            throw std::runtime_error("MeshManager::getMesh: Invalid file:'" + path.string() + "'");
        }

        // search for a suitable loader
        for (std::unique_ptr<MeshLoader> &loader : this->impl->loaders) {
            if (loader->isSupported(path.string()) == true) {
                auto meshPtr = loader->load(path.string(), graphicsDriver);

                mesh = meshPtr.get();

                this->impl->meshes[path.string()] = std::move(meshPtr);
                break;
            }
        }

        return mesh;
    }

	Mesh* MeshManager::generateBoxMesh(const std::string &id, const VertexFormat *vertexFormat, IndexFormat::Enum indexFormat, const Vector3f &center, const Vector3f &size) {
		assert(this->impl != nullptr);

#if defined(EXENG_DEBUG)
		this->impl->checkMeshId(id);
#endif	

		Matrix4f transformation = identity<float, 4>() * scale<float, 4>(size) * translate<float>(center);

		MeshPtr mesh = this->impl->generateMesh<BoxGenerator>(vertexFormat, indexFormat, transformation);

		return this->impl->storeMesh(id, std::move(mesh));
	}

	void MeshManager::setPath(const std::string &path) {
		assert(this->impl != nullptr);

		fs::path checkPath(path);

		if (!fs::exists(checkPath) || !fs::is_directory(path)) {
			throw std::runtime_error("MeshManager::setPath: the path '" + path + "' is not a valid directory.");
		}

		this->impl->path = path;
	}

	std::string MeshManager::getPath() const {
		assert(this->impl != nullptr);
		return this->impl->path;
	}

	void MeshManager::setGraphicsDriver(GraphicsDriver *driver) {
		assert(this->impl != nullptr);
		this->impl->graphicsDriver = driver;
	}

	GraphicsDriver* MeshManager::getGraphicsDriver() {
		assert(this->impl != nullptr);
		return this->impl->graphicsDriver;
	}

	const GraphicsDriver* MeshManager::getGraphicsDriver() const {
		assert(this->impl != nullptr);

		return this->impl->graphicsDriver;
	}

    Mesh* MeshManager::generateScreenMesh(const std::string &id, const VertexFormat *vertexFormat, IndexFormat::Enum indexFormat) {
        assert(this->impl != nullptr);

#if defined(EXENG_DEBUG)
		this->impl->checkMeshId(id);
#endif	

		Matrix4f transformation = translate<float>({0.5f, 0.5f, 0.0f});

		MeshPtr mesh = this->impl->generateMesh<RectGenerator>(vertexFormat, indexFormat, transformation);

		return this->impl->storeMesh(id, std::move(mesh));
    }
}}
