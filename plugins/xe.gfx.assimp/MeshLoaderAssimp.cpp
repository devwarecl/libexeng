
#include "MeshLoaderAssimp.hpp"

#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/MaterialLibrary.hpp>
#include <xe/gfx/TextureManager.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace xe { namespace gfx {

	MeshLoaderAssimp::~MeshLoaderAssimp() {}

	bool MeshLoaderAssimp::isSupported(const std::string &id) {
		return true;
	}

	std::vector<Material*> MeshLoaderAssimp::loadMaterials(const aiScene *aiscene) {
		std::vector<Material*> materials;
		
		// MaterialFormat format = this->getMaterialLibrary()->getFormat();
		
		for (unsigned int i=0; i<aiscene->mNumMaterials; i++) {
			Material *material = this->getMaterialLibrary()->createMaterial();

			aiMaterial *aimaterial = aiscene->mMaterials[i];
			aiString diffuseTextureId, specularTextureId, heightTextureId;

			// TODO: Consider other texture types
			// TODO: Consider the material format
			aimaterial->GetTexture(aiTextureType_DIFFUSE, 0, &diffuseTextureId);
			aimaterial->GetTexture(aiTextureType_SPECULAR, 0, &specularTextureId);
			aimaterial->GetTexture(aiTextureType_HEIGHT, 0, &heightTextureId);

			material->getLayer(0)->setTexture( this->getTextureManager()->getTexture(diffuseTextureId.C_Str()) );
			material->getLayer(1)->setTexture( this->getTextureManager()->getTexture(specularTextureId.C_Str()) );
			material->getLayer(2)->setTexture( this->getTextureManager()->getTexture(heightTextureId.C_Str()) );

			materials.push_back(material);
		}

		return materials;
	}

	MeshPtr MeshLoaderAssimp::load(const std::string &id) {
		Assimp::Importer importer;

		auto *aiscene = importer.ReadFile(id, aiProcess_Triangulate);

		if (!aiscene || !aiscene->HasMeshes()) {
			return MeshPtr();
		}

		std::vector<Material*> materials = this->loadMaterials(aiscene);
		std::vector<MeshSubsetPtr> subsets;

		for (unsigned int i=0; i<aiscene->mNumMeshes; i++) {
			auto *aimesh = aiscene->mMeshes[i];

			std::vector<StandardVertex> vertices;
			std::vector<int> indices;

			// extract vertex data
			// TODO: Use the VertexArray template class for vertex processing independent of vertexformat 
			for (unsigned int j=0; j<aimesh->mNumVertices; j++) {
				StandardVertex vertex;

				vertex.coord = Vector3f(&aimesh->mVertices[j].x);
				
				if (aimesh->HasNormals()) {
					vertex.normal = Vector3f(&aimesh->mNormals[j].x);
				}

				if (aimesh->HasTextureCoords(0)) {
					vertex.texCoord = Vector2f(&aimesh->mTextureCoords[0][j].x);
				}

				vertices.push_back(vertex);
			}

			// extract index data
			for (unsigned int j=0; j<aimesh->mNumFaces; j++) {
				aiFace &face = aimesh->mFaces[j];

				for (unsigned int k=0; k<face.mNumIndices; k++) {
					indices.push_back(face.mIndices[k]);
				}
			}

			// create vertex buffer and index buffer
			auto vbuffer = this->getGraphicsDriver()->createVertexBuffer(vertices);
			auto ibuffer = this->getGraphicsDriver()->createIndexBuffer(indices);

			// create mesh subset 
			auto subset = this->getGraphicsDriver()->createMeshSubset (
				std::move(vbuffer), &format,
				std::move(ibuffer), IndexFormat::Index32
			);

			// create the material
			Material *material = materials[aimesh->mMaterialIndex];

			// 
			subset->setMaterial(material);
			subset->setPrimitive(Primitive::TriangleList);

			subsets.push_back(std::move(subset));
		}

		return std::make_unique<Mesh>(std::move(subsets));
	}
}}
