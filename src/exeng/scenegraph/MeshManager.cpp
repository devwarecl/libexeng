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
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <exeng/scenegraph/IMeshLoader.hpp>
#include <exeng/scenegraph/MeshPart.hpp>
#include <exeng/scenegraph/Mesh.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>

namespace exeng { namespace scenegraph {
    using namespace exeng::graphics;
    
    /**
     * @brief Simple mesh loader. 
     */
    class CubeMeshLoader : public IMeshLoader {
    public:
        virtual ~CubeMeshLoader() {}
        
        virtual bool isSupported(const std::string &filename) override {
            return filename == "//cube";
        }
        
        virtual std::unique_ptr<Mesh> loadMesh(const std::string &filename, GraphicsDriver *graphicsDriver) override {
            auto vertexBuffer = this->generateCubeVertices(graphicsDriver);
            auto indexBuffer = this->generateCubeIndices(graphicsDriver);
            auto subset = graphicsDriver->createMeshSubset(std::move(vertexBuffer), std::move(indexBuffer), VertexFormat::makeVertex());

            return std::unique_ptr<Mesh>(new Mesh(std::move(subset)));
        }

    private:
        std::unique_ptr<Buffer> generateCubeVertices(GraphicsDriver *graphicsDriver) const {
            Vertex vertices[] = {
                // Cara izquierda
                {{-0.5f,   0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {0.0f, 1.0f}},
                {{ 0.5f,   0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {1.0f, 1.0f}},
                {{-0.5f,  -0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {0.0f, 0.0f}},
                {{ 0.5f,  -0.5f, -0.5f},   {0.0f, 0.0f, -1.0f},  {1.0f, 0.0f}},
                
                // Cara derecha
                {{0.5f,   0.5f, -0.5f},   {1.0f, 0.0f, 0.0f},   {0.0f, 1.0f}},
                {{0.5f,   0.5f,  0.5f},   {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}}, 
                {{0.5f,  -0.5f, -0.5f},   {1.0f, 0.0f, 0.0f},   {0.0f, 0.0f}}, 
                {{0.5f,  -0.5f,  0.5f},   {1.0f, 0.0f, 0.0f},   {1.0f, 0.0f}}, 
                
                // Cara delantera
                {{ 0.5f,   0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {1.0f, 1.0f}},
                {{-0.5f,   0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {0.0f, 1.0f}},
                {{ 0.5f,  -0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {1.0f, 0.0f}},
                {{-0.5f,  -0.5f,  0.5f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},
                
                // Cara Izquierda
                {{-0.5f,   0.5f,  0.5f},  {-1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}},
                {{-0.5f,   0.5f, -0.5f},  {-1.0f, 0.0f, 0.0f},   {0.0f, 1.0f}},
                {{-0.5f,  -0.5f,  0.5f},  {-1.0f, 0.0f, 0.0f},   {1.0f, 0.0f}},
                {{-0.5f,  -0.5f, -0.5f},  {-1.0f, 0.0f, 0.0f},   {0.0f, 0.0f}},
                
                // Cara de Arriba
                {{-0.5f,   0.5f,   0.5f},  {0.0f, 1.0f, 0.0f},   {0.0f, 1.0f}},
                {{ 0.5f,   0.5f,   0.5f},  {0.0f, 1.0f, 0.0f},   {1.0f, 1.0f}},
                {{-0.5f,   0.5f,  -0.5f},  {0.0f, 1.0f, 0.0f},   {0.0f, 0.0f}},
                {{ 0.5f,   0.5f,  -0.5f},  {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},
                
                // Cara Inferior
                {{ 0.5f,  -0.5f,   0.5f},  {0.0f, -1.0f, 0.0f},   {1.0f, 1.0f}},
                {{-0.5f,  -0.5f,   0.5f},  {0.0f, -1.0f, 0.0f},   {0.0f, 1.0f}},
                {{ 0.5f,  -0.5f,  -0.5f},  {0.0f, -1.0f, 0.0f},   {1.0f, 0.0f}}, 
                {{-0.5f,  -0.5f,  -0.5f},  {0.0f, -1.0f, 0.0f},   {0.0f, 0.0f}}
            };

            return graphicsDriver->createVertexBuffer(sizeof(vertices), vertices);
        }
        
        std::unique_ptr<Buffer> generateCubeIndices(GraphicsDriver *graphicsDriver) const {
            int indices[] = {
                0 + 0,  0 + 1,  0 + 2,      0 + 1,  0 + 3,  0 + 2,
                4 + 0,  4 + 1,  4 + 2,      4 + 1,  4 + 3,  4 + 2, 
                8 + 0,  8 + 1,  8 + 2,      8 + 1,  8 + 3,  8 + 2, 
                12 + 0, 12 + 1, 12 + 2,     12 + 1, 12 + 3, 12 + 2, 
                16 + 0, 16 + 1, 16 + 2,     16 + 1, 16 + 3, 16 + 2, 
                20 + 0, 20 + 1, 20 + 2,     20 + 1, 20 + 3, 20 + 2
            };

            return graphicsDriver->createIndexBuffer(sizeof(indices), indices);
        }
    };
}}

namespace exeng { namespace scenegraph {
    struct MeshManager::Private  {
        std::list<std::unique_ptr<IMeshLoader>> loaders;
        std::map<std::string, std::unique_ptr<Mesh>> meshes;
    };
    
    MeshManager::MeshManager() : impl(new MeshManager::Private()) {
        this->addMeshLoader(new CubeMeshLoader());
    }
    
    MeshManager::~MeshManager() { 
        delete impl;
    }
    
    void MeshManager::addMeshLoader(IMeshLoader *loader) {
        this->impl->loaders.push_front(std::unique_ptr<IMeshLoader>(loader));
    }
    
    void MeshManager::removeMeshLoader(IMeshLoader *loader) {
        this->impl->loaders.remove(std::unique_ptr<IMeshLoader>(loader));
    }
    
    Mesh* MeshManager::getMesh(const std::string &filename, GraphicsDriver *graphicsDriver) {
        Mesh* mesh = nullptr;
        
        // search the mesh
        auto meshIterator = this->impl->meshes.find(filename);

        if (meshIterator != std::end(this->impl->meshes)) {
            return meshIterator->second.get();
        }

        // search for a suitable loader
        for (std::unique_ptr<IMeshLoader> &loader : this->impl->loaders) {
            if (loader->isSupported(filename) == true) {
                auto meshPtr = loader->loadMesh(filename, graphicsDriver);

                mesh = meshPtr.get();

                this->impl->meshes[filename] = std::move(meshPtr);
                break;
            }
        }

        return mesh;
    }
}}
