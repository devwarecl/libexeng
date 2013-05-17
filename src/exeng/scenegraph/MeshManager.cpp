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
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/range/algorithm/find_if.hpp>

#include "IMeshLoader.hpp"

namespace exeng {
    namespace scenegraph {
        
        struct MeshManager::Private  {
            boost::ptr_list<IMeshLoader> loaders;
        };
    
        
        MeshManager::MeshManager() : impl(new MeshManager::Private()) {}
        
        MeshManager::~MeshManager() {}
        
        
        void MeshManager::addMeshLoader(IMeshLoader *loader) {
            this->impl->loaders.push_back(loader);
        }
        
        
        Mesh* MeshManager::loadMesh(const char* filename) {
            // Search for the first loader.
            for (auto& loader : this->impl->loaders) {
                if (loader.isSupported(filename) == true) {
                    return loader.loadMesh(filename);
                }
            }
            
            return nullptr;
        }
    }
}
