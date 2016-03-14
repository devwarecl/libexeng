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

#include <xe/Vector.hpp>
#include <xe/ProductManagerImpl.hpp>
#include <xe/gfx/MeshSubsetGenerator.hpp>
#include <xe/gfx/Algorithm.hpp>
#include <xe/gfx/MeshLoader.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/gfx/GraphicsDriver.hpp>

namespace fs = boost::filesystem;

namespace xe { namespace gfx {
	
    struct MeshManager::Private {
		ProductManagerImpl<MeshLoader, Mesh> manager;
		GraphicsDriver *driver = nullptr;
		MaterialLibrary *library = nullptr;
		TextureManager *textureManager = nullptr;
		
		Mesh* storeMesh(const std::string &id, MeshPtr mesh) {
			Mesh* meshPtr = mesh.get();

			manager.putProduct(id, std::move(mesh));

			return meshPtr;
		}
    };
    
    MeshManager::MeshManager() {
        impl = new MeshManager::Private();
    }
    
    MeshManager::~MeshManager() {
        delete impl;
    }
    
    void MeshManager::addMeshLoader(MeshLoader *loader) {
		assert(impl);

		loader->setGraphicsDriver(getGraphicsDriver());
		loader->setMaterialLibrary(getMaterialLibrary());
		loader->setTextureManager(getTextureManager());

        impl->manager.addLoader(loader);
    }
    
    void MeshManager::removeMeshLoader(MeshLoader *loader) {
		assert(impl);

		loader->setGraphicsDriver(nullptr);
		loader->setMaterialLibrary(nullptr);
		loader->setTextureManager(nullptr);

        impl->manager.removeLoader(loader);
    }
    
    Mesh* MeshManager::getMesh(const std::string &filename) {
		assert(impl);

		return impl->manager.getProduct(filename);
    }

	Mesh* MeshManager::getMesh(const std::string &id, MeshPtr mesh)  {
		assert(impl);

		return impl->storeMesh(id, std::move(mesh));
	}

	void MeshManager::setGraphicsDriver(GraphicsDriver *driver) {
		assert(impl);

		auto loaders = impl->manager.getLoaders();
		for (MeshLoader *loader : loaders) {
			loader->setGraphicsDriver(driver);
		}

		impl->driver = driver;
	}

	GraphicsDriver* MeshManager::getGraphicsDriver() {
		assert(impl);

		return impl->driver;
	}

	void MeshManager::setMaterialLibrary(MaterialLibrary *library) {
		assert(impl);

		auto loaders = impl->manager.getLoaders();
		for (MeshLoader *loader : loaders) {
			loader->setMaterialLibrary(library);
		}

		impl->library = library;
	}

	MaterialLibrary* MeshManager::getMaterialLibrary() {
		assert(impl);

		return impl->library;
	}

	void MeshManager::setTextureManager(TextureManager *textureManager) {
		assert(impl);

		auto loaders = impl->manager.getLoaders();
		for (MeshLoader *loader : loaders) {
			loader->setTextureManager(textureManager);
		}

		impl->textureManager = textureManager;
	}

	TextureManager * MeshManager::getTextureManager() {
		assert(impl);
		
		return impl->textureManager;
	}
}}
