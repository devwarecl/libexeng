/**
 * @file MeshManager.hpp
 * @brief MeshManager class definition.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_MESHMANAGER_HPP__
#define __EXENG_SCENEGRAPH_MESHMANAGER_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <xe/Config.hpp>
#include <xe/Vector.hpp>
#include <xe/Size.hpp>
#include <xe/gfx/VertexFormat.hpp>
#include <xe/gfx/IndexFormat.hpp>
#include <xe/gfx/Forward.hpp>
#include <xe/gfx/MeshSubset.hpp>
#include <xe/gfx/Mesh.hpp>

namespace xe { namespace gfx {
    /**
    * @brief Mesh manager class.
    */
    class EXENGAPI MeshManager {
    public:
        MeshManager();
        virtual ~MeshManager();
        
		/**
         * @brief Set the default location to search for mesh files when a non-full
		 * path is given.
         */
		// void setPath(const std::string &path);

		/**
         * @brief Get the default location for mesh files.
         */
		// std::string getPath() const;

        /**
         * @brief Add a new mesh loader in the mesh manager.
         */
        void addMeshLoader(MeshLoader *loader);
        
        /**
         * @brief Remove a mesh loader in the mesh manager
         */
        void removeMeshLoader(MeshLoader *loader);
        
        /**
         * @brief Load a mesh from the specified file, or get the mesh from the specified id.
         */
        Mesh* getMesh(const std::string &id);

        /**
         * @brief 
         */
        Mesh* getMesh(const std::string &id, MeshSubsetPtr subset);

        /**
         * @brief 
         */
        Mesh* getMesh(const std::string &id, std::vector<MeshSubsetPtr> subsets);

		/**
		 * @brief Register a mesh with the specified id.
		 */
		Mesh* getMesh(const std::string &id, MeshPtr mesh);

    private:
        struct Private;
        Private *impl = nullptr;
    };
}}

#endif // __EXENG_SCENEGRAPH_MESHMANAGER_HPP__
