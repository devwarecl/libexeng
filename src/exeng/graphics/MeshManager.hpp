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

#include <exeng/Config.hpp>
#include <exeng/Vector.hpp>
#include <exeng/Size.hpp>
#include <exeng/graphics/VertexFormat.hpp>
#include <exeng/graphics/IndexFormat.hpp>
#include <exeng/graphics/Forward.hpp>

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
         * @brief Load a mesh from the specified file.
         */
        Mesh* getMesh(const std::string &id);

		/**
		 * @brief Generate a box shaped mesh
		 */
		Mesh* generateBoxMesh(const std::string &id, GraphicsDriver *driver, const VertexFormat *vertexFormat, IndexFormat::Enum indexFormat, const Vector3f &center, const Vector3f &size);

        /**
		 * @brief Generate a rectangle mesh (for two-dimensional rendering)
		 */
        Mesh* generateScreenMesh(const std::string &id, GraphicsDriver *driver, const VertexFormat *vertexFormat, IndexFormat::Enum indexFormat);

    private:
        struct Private;
        Private *impl = nullptr;
    };
}}

#endif // __EXENG_SCENEGRAPH_MESHMANAGER_HPP__
