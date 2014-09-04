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

namespace exeng { namespace graphics {
    class EXENGAPI GraphicsDriver; 
}}

namespace exeng { namespace scenegraph {
    class EXENGAPI Mesh;    
    class EXENGAPI IMeshLoader;

    /**
    * @brief Mesh manager class.
    */
    class EXENGAPI MeshManager {
    public:
        MeshManager();
        ~MeshManager();
        
        /**
         * @brief Add a new mesh loader in the mesh manager.
         */
        void addMeshLoader(IMeshLoader *loader);
        
        /**
         * @brief Remove a mesh loader in the mesh manager
         */
        void removeMeshLoader(IMeshLoader *loader);
        
        /**
         * @brief Load a mesh from the specified file.
         */
        Mesh* getMesh(const std::string &filename, exeng::graphics::GraphicsDriver *graphicsDriver);

    private:
        struct Private;
        Private *impl = nullptr;
    };
}}

#endif // __EXENG_SCENEGRAPH_MESHMANAGER_HPP__
