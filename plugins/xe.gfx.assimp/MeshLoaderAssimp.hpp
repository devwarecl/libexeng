
#pragma once 

#ifndef __xe_gfx_meshloaderassimp_hpp__
#define __xe_gfx_meshloaderassimp_hpp__

#include <xe/gfx/MeshLoader.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/gfx/Vertex.hpp>

#include <assimp/scene.h>

namespace xe { namespace gfx {

	class AssimpMeshLoader : public xe::gfx::MeshLoader {
	public:
		virtual ~AssimpMeshLoader();

		virtual bool isSupported(const std::string &id) override;

		virtual MeshPtr load(const std::string &id) override;

	private:
		std::vector<Material*> loadMaterials(const aiScene *aiscene);

	private:
		VertexFormat format = StandardVertex::getFormat();
	};
}}

#endif
