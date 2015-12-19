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


#ifndef __EXENG_SCENEGRAPH_IMESHLOADER_HPP__
#define __EXENG_SCENEGRAPH_IMESHLOADER_HPP__

#include <exeng/Config.hpp>
#include <exeng/graphics/Forward.hpp>
#include <string>
#include <memory>

namespace xe { namespace gfx {
    /**
     * @brief Mesh loader interface.
     */
    class EXENGAPI MeshLoader {
    public:
		MeshLoader();

        virtual ~MeshLoader();
        
		void setGraphicsDriver(GraphicsDriver *driver);

		GraphicsDriver* getGraphicsDriver();

        /**
         * @brief Check if the specified filename extension is supported by the current loader.
         * @param filename Raw string to the filename to check. 
         */
        virtual bool isSupported(const std::string &filename) = 0;
        
        /**
         * @brief Load the mesh contained in the specified file.
         */
        virtual std::unique_ptr<Mesh> load(const std::string &filename) = 0;

	private:
		GraphicsDriver *graphicsDriver = nullptr;
    };
}}
        
#endif // __EXENG_SCENEGRAPH_IMESHLOADER_HPP__
