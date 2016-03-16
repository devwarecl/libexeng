/**
 * @file MeshLoader.hpp
 * @brief MeshLoader interface definition. 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __xe_gfx_meshloader_hpp__
#define __xe_gfx_meshloader_hpp__

#include <xe/Config.hpp>
#include <xe/gfx/Forward.hpp>
#include <xe/gfx/Mesh.hpp>
#include <string>
#include <memory>

namespace xe { namespace gfx {
    /**
     * @brief Mesh loader interface.
	 * @todo Specify the desired vertex format
     */
    class EXENGAPI MeshLoader {
    public:
		MeshLoader();

        virtual ~MeshLoader();
        
		void setGraphicsDriver(GraphicsDriver *driver);

		GraphicsDriver* getGraphicsDriver();

		void setMaterialLibrary(MaterialLibrary *materialLibrary);

		MaterialLibrary* getMaterialLibrary();

		void setTextureManager(TextureManager *textureManager);

		TextureManager* getTextureManager();

        /**
         * @brief Check if the specified filename extension is supported by the current loader.
         * @param filename Raw string to the filename to check. 
         */
        virtual bool isSupported(const std::string &filename) = 0;
        
        /**
         * @brief Load the mesh contained in the specified file.
         */
        virtual MeshPtr load(const std::string &filename) = 0;

	private:
		GraphicsDriver *graphicsDriver = nullptr;
		MaterialLibrary *materialLibrary = nullptr;
		TextureManager *textureManager = nullptr;
    };
}}
        
#endif
