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
#include <list>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/filesystem/path.hpp>

#include <exeng/Vector.hpp>
#include <exeng/scenegraph/IMeshLoader.hpp>
#include <exeng/scenegraph/MeshPart.hpp>
#include <exeng/scenegraph/Mesh.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>

#include <lwobject/lwo2.h>

namespace exeng { namespace scenegraph {
    using namespace exeng::graphics;
    
	std::vector<Vertex> generateBoxVertices(const Vector3f &center, const Vector3f &size)
	{
		std::vector<Vertex> vertices = {
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

		for (Vertex &vertex : vertices) {
			vertex.coord = (vertex.coord*size) + center;
		}

		return vertices;
	}

	std::vector<int> generateBoxIndices() 
	{
        std::vector<int> indices = {
            0 + 0,  0 + 1,  0 + 2,      0 + 1,  0 + 3,  0 + 2,
            4 + 0,  4 + 1,  4 + 2,      4 + 1,  4 + 3,  4 + 2, 
            8 + 0,  8 + 1,  8 + 2,      8 + 1,  8 + 3,  8 + 2, 
            12 + 0, 12 + 1, 12 + 2,     12 + 1, 12 + 3, 12 + 2, 
            16 + 0, 16 + 1, 16 + 2,     16 + 1, 16 + 3, 16 + 2, 
            20 + 0, 20 + 1, 20 + 2,     20 + 1, 20 + 3, 20 + 2
        };

		return indices;
	}

    /**
     * @brief Simple mesh loader. 
     */
    class CubeMeshLoader : public IMeshLoader {
    public:
        virtual ~CubeMeshLoader() {}
        
        virtual bool isSupported(const std::string &filename) override 
		{
            return filename == "/cube";
        }
        
        virtual std::unique_ptr<Mesh> loadMesh(const std::string &filename, GraphicsDriver *graphicsDriver) override 
		{
			auto vertexBuffer = graphicsDriver->createVertexBuffer(generateBoxVertices({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}));
            auto indexBuffer = graphicsDriver->createIndexBuffer(generateBoxIndices());
            auto subset = graphicsDriver->createMeshSubset(std::move(vertexBuffer), std::move(indexBuffer), VertexFormat::makeVertex());

            return std::unique_ptr<Mesh>(new Mesh(std::move(subset)));
        }
    };

	class LwoMeshLoader : public IMeshLoader {
	public:
		virtual bool isSupported(const std::string &filename) override 
		{
			return boost::filesystem::path(filename).extension() == "lwo";
        }

		virtual std::unique_ptr<Mesh> loadMesh(const std::string &filename, GraphicsDriver *graphicsDriver) override 
		{
			auto vertexBuffer = graphicsDriver->createVertexBuffer(generateBoxVertices({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}));
            auto indexBuffer = graphicsDriver->createIndexBuffer(generateBoxIndices());

            auto subset = graphicsDriver->createMeshSubset(std::move(vertexBuffer), std::move(indexBuffer), VertexFormat::makeVertex());

            return std::unique_ptr<Mesh>(new Mesh(std::move(subset)));
        }

	private:

		/**
		 * @brief Texture proyection
		 */
		enum lwProj {
			LW_PROJ_PLANAR = 0,
			LW_PROJ_CYLINDRICAL = 1,
			LW_PROJ_SPHERICAL = 2,
			LW_PROJ_CUBIC = 3,
			LW_PROJ_FRONT = 4,
			LW_PROJ_UV = 5
		};

		enum lwAxis {
			LW_AXIS_X = 0,
			LW_AXIS_Y = 1,
			LW_AXIS_Z = 2
		};

		/**
		 * @brief Automatically generate the index array from the specified polygon size
		 */
		static void appendIndices(std::vector<int> &indices, int polygonSize, int indexBase, bool invert) 
		{
			if (invert) {
				for(int j=1; j<polygonSize-1; j++) {
					indices.push_back(indexBase + 0);
					indices.push_back(indexBase + j);
					indices.push_back(indexBase + j + 1);
				}
			} else {
				for(int j=1; j<polygonSize-1; j++) {
					indices.push_back(indexBase + 0);
					indices.push_back(indexBase + j + 1);
					indices.push_back(indexBase + j);
				}
			}
		}

		/**
		 * @brief Search a clip with the specified index (id)
		 */
		static lwClip* findClipFromIndex(lwObject* Object, int index)
		{
			//Recorrer los clips hasta dar con el que tenga el índice indicado
			lwClip *outClip = nullptr;
			for (outClip=Object->clip; outClip!=nullptr; outClip=outClip->next) {
				if (outClip->index == index) {
					break;
				}
			}

			return outClip;
		}

		/**
		 * @brief Pending.
		 */
		static Vector3f setupTexturePoint(const Vector3f &point, const Vector3f &center, const Vector3f &ypr, const Vector3f &size, lwProj proj)
		{
			Vector3f q = point - center;

			q = exeng::transform(exeng::rotate<float>(ypr.z, { 0.0f, 0.0f, -1.0f}), q);
			q = exeng::transform(exeng::rotate<float>(ypr.y, { 0.0f, 1.0f,  0.0f}), q);
			q = exeng::transform(exeng::rotate<float>(ypr.x, {-1.0f, 0.0f,  0.0f}), q);

			if (proj != LW_PROJ_SPHERICAL) {
				q = q / size;
			}

			return q;
		}

		static Vector3f computePolygonNormal(const lwPolygon *poly, const lwPointList *points, bool invertNormal)
		{
			Vector3f normal = {0.0f, 0.0f, 0.0f};

			if (poly->nverts >= 3) {
				Vector3f a = Vector3f(points->pt[ poly->v[0].index ].pos);
				Vector3f b = Vector3f(points->pt[ poly->v[1].index ].pos);
				Vector3f c = Vector3f(points->pt[ poly->v[2].index ].pos);

				normal = exeng::normalize(exeng::cross(b-a, c-a));

				if (invertNormal) {
					normal = -normal;
				}
			}

			return normal;
		}

		static float cylindricalAngle(float x, float y)
		{
			const float pi = exeng::Pi<float>::Value;
			const float pi_2 = pi * 0.5f;

			float r = std::sqrt(x*x + y*y);
			float a = 0.0f;

			if (r == 0.0f)  {
				return 0.0f;
			}

			x /= r;

			if (x < 0.0f && y >= 0.0f) {
				a = pi_2 - acosf(-x);
			} else if (x < 0.0f && y < 0.0f) {
				a = acosf(-x) + pi_2;
			} else if (x >= 0.0f && y >= 0.0f) {
				a = acosf(x) + 3.0f * pi_2;
			} else if (x >= 0.0f && y < 0.0f) {
				a = 3.0f * pi_2 - acosf(x);
			} else {
				a = 0.0f;
			}

			return a/pi/2.0f;
		}

		static lwVMap* findVMap(lwVMap* Map, const std::string &vmapname, unsigned int type)
		{
			lwVMap* VMap = nullptr;

			for(VMap=Map; VMap!=nullptr; VMap=VMap->next) {
				if ((vmapname == VMap->name) && (type == VMap->type)){
					break;
				}
			}

			//Volver a buscar un vmap con el mismo nombre, pero mejor.
			if ((VMap != nullptr) && (type == ID_TXUV)) {
				lwVMap* BetterVMap = findVMap(VMap->next, vmapname, ID_TXUV);

				if (BetterVMap != nullptr) {
					VMap = BetterVMap;
				}
			}

			return VMap;
		}

		static lwVMap* getVMap(lwLayer* Layer, char* Name, bool Continuous)
		{
			lwVMap* VMap = nullptr;

			for(VMap=Layer->vmap; VMap!=nullptr; VMap=VMap->next) {
				if (std::string(Name) == std::string(VMap->name)) {
					if (Continuous==true) {
						if (VMap->pindex==nullptr) {
							return VMap;
						}
					} else {
						if (VMap->pindex!=nullptr) {
							return VMap;
						}
					}
				}
			}

			return nullptr;
		}

		static void buildMeshSubset(std::unique_ptr<MeshSubset> &meshSubset, lwLayer *layer, lwSurface *surf)
		{

		}
	};

}}

namespace exeng { namespace scenegraph {
    struct MeshManager::Private {
        std::list<std::unique_ptr<IMeshLoader>> loaders;
        std::map<std::string, std::unique_ptr<Mesh>> meshes;
    };
    
    MeshManager::MeshManager() : impl(new MeshManager::Private()) 
	{
        this->addMeshLoader(new CubeMeshLoader());
    }
    
    MeshManager::~MeshManager() 
	{
        delete impl;
    }
    
    void MeshManager::addMeshLoader(IMeshLoader *loader) 
	{
		assert(this->impl != nullptr);

        this->impl->loaders.push_front(std::unique_ptr<IMeshLoader>(loader));
    }
    
    void MeshManager::removeMeshLoader(IMeshLoader *loader) 
	{
		assert(this->impl != nullptr);

        this->impl->loaders.remove(std::unique_ptr<IMeshLoader>(loader));
    }
    
    Mesh* MeshManager::getMesh(const std::string &filename, GraphicsDriver *graphicsDriver) 
	{
		assert(this->impl != nullptr);

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

	Mesh* MeshManager::generateBoxMesh(const std::string &id, exeng::graphics::GraphicsDriver *graphicsDriver, const Vector3f &center, const Vector3f &size)
	{
		assert(this->impl != nullptr);

		auto &meshes = this->impl->meshes;

#if defined(EXENG_DEBUG)
		if (meshes.find(id) != meshes.end()) {
			throw std::runtime_error("MeshManager::generateBoxMesh: The mesh id '" + id + "' already exists.");
		}
#endif

		std::vector<Vertex> vertices = generateBoxVertices(center, size);
		std::vector<int> indices = generateBoxIndices();

		auto vertexBuffer = graphicsDriver->createVertexBuffer(vertices);
		auto indexBuffer = graphicsDriver->createIndexBuffer(indices);

		auto subset = graphicsDriver->createMeshSubset(std::move(vertexBuffer), std::move(indexBuffer), VertexFormat::makeVertex());
		auto mesh = std::unique_ptr<Mesh>(new Mesh(std::move(subset)));

		meshes[id] = std::move(mesh);

		return meshes[id].get();
	}
}}
