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


#include <map>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/range/algorithm/find_if.hpp>

#include <exeng/scenegraph/IMeshLoader.hpp>
#include <exeng/scenegraph/MeshManager.hpp>

#include <exeng/scenegraph/MeshPart.hpp>
#include <exeng/scenegraph/Mesh.hpp>

#include <exeng/graphics/HeapVertexBuffer.hpp>
#include <exeng/graphics/HeapIndexBuffer.hpp>

namespace exeng { namespace scenegraph {
    using namespace exeng::graphics;
    
    /**
     * @brief Simple mesh loader. 
     */
    class CubeMeshLoader : public IMeshLoader {
    public:
        virtual ~CubeMeshLoader() {}
        
    private:
        VertexBuffer* generateCubeVertices() const {
            VertexBuffer *vertexBuffer = new HeapVertexBuffer(nullptr, VertexFormat::makeVertex(), 24);
            
            Vertex* vertices = static_cast<Vertex*>(vertexBuffer->lock());
            
            vertices[0] = {{-0.5f,   0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {0.0f, 1.0f}};
            vertices[1] = {{ 0.5f,   0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {1.0f, 1.0f}};  
            vertices[2] = {{-0.5f,  -0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {0.0f, 0.0f}};  
            vertices[3] = {{ 0.5f,  -0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {1.0f, 0.0f}};  
        
            // Cara derecha
            vertices[4] = {{0.5f,   0.5f, -0.5f},   {1.0f, 0.0f, 0.0f},   {0.0f, 1.0f}}; 
            vertices[5] = {{0.5f,   0.5f,  0.5f},   {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}}; 
            vertices[6] = {{0.5f,  -0.5f, -0.5f},   {1.0f, 0.0f, 0.0f},   {0.0f, 0.0f}}; 
            vertices[7] = {{0.5f,  -0.5f,  0.5f},   {1.0f, 0.0f, 0.0f},   {1.0f, 0.0f}}; 
        
            // Cara delantera
            vertices[8] = {{ 0.5f,   0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {1.0f, 1.0f}};  
            vertices[9] = {{-0.5f,   0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {0.0f, 1.0f}};  
            vertices[10] = {{ 0.5f,  -0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {1.0f, 0.0f}};  
            vertices[11] = {{-0.5f,  -0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}};  
            
            // Cara Izquierda
            vertices[12] = {{-0.5f,   0.5f,  0.5f},  {-1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}}; 
            vertices[13] = {{-0.5f,   0.5f, -0.5f},  {-1.0f, 0.0f, 0.0f},   {0.0f, 1.0f}}; 
            vertices[14] = {{-0.5f,  -0.5f,  0.5f},  {-1.0f, 0.0f, 0.0f},   {1.0f, 0.0f}}; 
            vertices[15] = {{-0.5f,  -0.5f, -0.5f},  {-1.0f, 0.0f, 0.0f},   {0.0f, 0.0f}}; 
            
            // Cara de Arriba
            vertices[16] = {{-0.5f,   0.5f,   0.5f},  {0.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}; 
            vertices[17] = {{ 0.5f,   0.5f,   0.5f},  {0.0f, 1.0f, 0.0f},   {1.0f, 1.0f}}; 
            vertices[18] = {{-0.5f,   0.5f,  -0.5f},  {0.0f, 1.0f, 0.0f},   {0.0f, 0.0f}}; 
            vertices[19] = {{ 0.5f,   0.5f,  -0.5f},  {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}};  
            
            // Cara Inferior
            vertices[20] = {{ 0.5f,  -0.5f,   0.5f},  {0.0f, -1.0f, 0.0f},   {1.0f, 1.0f}};
            vertices[21] = {{-0.5f,  -0.5f,   0.5f},  {0.0f, -1.0f, 0.0f},   {0.0f, 1.0f}}; 
            vertices[22] = {{ 0.5f,  -0.5f,  -0.5f},  {0.0f, -1.0f, 0.0f},   {1.0f, 0.0f}}; 
            vertices[23] = {{-0.5f,  -0.5f,  -0.5f},  {0.0f, -1.0f, 0.0f},   {0.0f, 0.0f}};  
            
            vertices = nullptr;
            
            vertexBuffer->unlock();
            
            return vertexBuffer;
        }
        
        IndexBuffer* generateCubeIndices() const {
            IndexBuffer *indexBuffer = new HeapIndexBuffer(nullptr, IndexFormat::Index32, 36);
            
            int *indices = static_cast<int*>(indexBuffer->lock());
            
            indices[0] = 0 + 0;   indices[1] = 0 + 1;   indices[2] = 0 + 2;  
            indices[3] = 0 + 1;   indices[4] = 0 + 3;   indices[5] = 0 + 2;
            indices[6] = 4 + 0;   indices[7] = 4 + 1;   indices[8] = 4 + 2;  
            indices[9] = 4 + 1;   indices[10] = 4 + 3;  indices[11] = 4 + 2; 
            indices[12] = 8 + 0;  indices[13] = 8 + 1;  indices[14] = 8 + 2;  
            indices[15] = 8 + 1;  indices[16] = 8 + 3;  indices[17] = 8 + 2; 
            indices[18] = 12 + 0; indices[19] = 12 + 1; indices[20] = 12 + 2; 
            indices[21] = 12 + 1; indices[22] = 12 + 3; indices[23] = 12 + 2; 
            indices[24] = 16 + 0; indices[25] = 16 + 1; indices[26] = 16 + 2; 
            indices[27] = 16 + 1; indices[28] = 16 + 3; indices[29] = 16 + 2; 
            indices[30] = 20 + 0; indices[31] = 20 + 1; indices[32] = 20 + 2; 
            indices[33] = 20 + 1; indices[34] = 20 + 3; indices[35] = 20 + 2;
            indices = nullptr;
            
            indexBuffer->unlock();
            
            return indexBuffer;
        }
        
        // IMeshLoader interface
    public:
        virtual bool isSupported(const std::string &filename) {
            return filename == "$cube$";
        }
        
        virtual Mesh* loadMesh(const std::string &filename) {
            Mesh *mesh = new Mesh(1);
            MeshPart *part = mesh->getPart(0);
            
            part->primitiveType = Primitive::TriangleList;
            part->vertexBuffer.reset(new HeapVertexBuffer(nullptr, VertexFormat::makeVertex(), 12));
            part->indexBuffer.reset(new HeapIndexBuffer(nullptr, IndexFormat::Index32, 36));
            
            return mesh;
        }
    };
}}

namespace exeng { namespace scenegraph {
    struct MeshManager::Private  {
        std::list< std::unique_ptr<IMeshLoader> > loaders;
    };
    
    MeshManager::MeshManager() : impl(new MeshManager::Private()) {
        this->addMeshLoader(new CubeMeshLoader());
    }
    
    MeshManager::~MeshManager() { 
        delete impl;
    }
    
    void MeshManager::addMeshLoader(IMeshLoader *loader) {
        this->impl->loaders.push_back(std::unique_ptr<IMeshLoader>(loader));
    }
    
    void MeshManager::removeMeshLoader(IMeshLoader *loader) {
        this->impl->loaders.remove(std::unique_ptr<IMeshLoader>(loader));
    }
    
    Mesh* MeshManager::getMesh(const std::string &filename) {
        Mesh* mesh = nullptr;
        
        for (std::unique_ptr<IMeshLoader> &loader : this->impl->loaders) {
            if (loader->isSupported(filename) == true) {
                mesh = loader->loadMesh(filename);
                break;
            }
        }
        
        return mesh;
    }
}}
