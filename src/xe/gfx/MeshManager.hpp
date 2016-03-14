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
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/TextureManager.hpp>

namespace xe { namespace gfx {
    /**
    * @brief Mesh manager class.
    */
    class EXENGAPI MeshManager {
    public:
        MeshManager();
        virtual ~MeshManager();
        
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
		 * @brief Register a mesh with the specified id.
		 */
		Mesh* getMesh(const std::string &id, MeshPtr mesh);

		void setGraphicsDriver(GraphicsDriver *driver);

		GraphicsDriver* getGraphicsDriver() ;

		void setMaterialLibrary(MaterialLibrary *library);

		MaterialLibrary* getMaterialLibrary();

		void setTextureManager(TextureManager *textureManager);

		TextureManager * getTextureManager();

    private:
        struct Private;
        Private *impl = nullptr;
    };
}}

#endif // __EXENG_SCENEGRAPH_MESHMANAGER_HPP__
