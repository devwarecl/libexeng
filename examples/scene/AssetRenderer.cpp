
#include "AssetRenderer.hpp"

#include <xe/gfx/Mesh.hpp>
#include <xe/sg/Light.hpp>

void AssetRenderer::render(xe::sg::Light *light) {
	auto module = driver->getModernModule();

	module->setProgramGlobal("light_position", light->getPosition());
	// module->setProgramGlobal("light_range", light->getRange());
}

void AssetRenderer::render(xe::sg::Camera *camera) {
}

void AssetRenderer::render(xe::sg::Geometry *geometry) {}

void AssetRenderer::render(xe::gfx::Mesh *mesh) {
	for (int i=0; i<mesh->getSubsetCount(); i++) {
		xe::gfx::MeshSubset *subset = mesh->getSubset(i);

		this->driver->setMaterial(subset->getMaterial());
		this->driver->setMeshSubset(subset);
	}
}

void AssetRenderer::setTransformation(const xe::Matrix4f &transformation) {
}
