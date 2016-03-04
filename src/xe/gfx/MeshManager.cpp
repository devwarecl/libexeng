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

		Mesh* storeMesh(const std::string &id, MeshPtr mesh) {
			Mesh* meshPtr = mesh.get();

			this->manager.putProduct(id, std::move(mesh));

			return meshPtr;
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

    Mesh* MeshManager::getMesh(const std::string &id, MeshSubsetPtr subset) {
        auto mesh = std::make_unique<Mesh>(std::move(subset));

        return this->impl->storeMesh(id, std::move(mesh));
    }

    Mesh* MeshManager::getMesh(const std::string &id, std::vector<MeshSubsetPtr> subsets) {
        auto mesh = std::make_unique<Mesh>(std::move(subsets));

        return this->impl->storeMesh(id, std::move(mesh));
    }

	Mesh* MeshManager::getMesh(const std::string &id, MeshPtr mesh)  {
		return this->impl->storeMesh(id, std::move(mesh));
	}
}}
