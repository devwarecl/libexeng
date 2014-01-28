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

#include <exeng/Config.hpp>

namespace exeng { namespace scenegraph {

class EXENGAPI Mesh;    
class EXENGAPI IMeshLoader;

/**
 * @brief Mesh manager class. Load meshes
 */
class EXENGAPI MeshManager {
public:
    MeshManager();
    ~MeshManager();
    
    /**
     * @brief Add a new mesh loader in the mesh manager.
     * @param loader
     */
    void addMeshLoader(IMeshLoader *loader);
    
    /**
     * @brief loadMesh
     * @param filename
     * @return 
     */
    Mesh* loadMesh(const char* filename);
    
private:
    struct Private;
    Private *impl;
};
        
}}

#endif // exeng_graphics_meshmanager_hpp
