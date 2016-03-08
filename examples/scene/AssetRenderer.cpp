
#include "AssetRenderer.hpp"

#include <xe/gfx/Mesh.hpp>
#include <xe/sg/Light.hpp>
#include <xe/sg/Camera.hpp>

AssetRenderer::AssetRenderer(xe::gfx::GraphicsDriver *driver_) : driver(driver_) {
	assert(driver);
	assert(driver->getModernModule());
	assert(driver->getModernModule()->getShaderProgram());
}

void AssetRenderer::render(xe::sg::Light *light) {
	assert(light);

	auto module = driver->getModernModule();

	module->setProgramParam("light_position", light->getPosition());
	module->setProgramParam("light_range", light->getRange());
}

void AssetRenderer::render(xe::sg::Camera *camera) {
	assert(camera);

	// TODO: compute projection matrix
	proj = xe::identity<float, 4>();

	// compute view matrix
	view = xe::lookat (
		camera->getPosition(),
		camera->getLookAt(),
		camera->getUp()
	);
}

void AssetRenderer::render(xe::sg::Geometry *geometry) {
	assert(geometry);
}

void AssetRenderer::render(xe::gfx::Mesh *mesh) {
	assert(mesh);
	assert(driver);

	// set the current full transformation matrix
	auto module = driver->getModernModule();

	module->setProgramMatrix("mvp", this->computeProjViewModel());

	for (int i=0; i<mesh->getSubsetCount(); i++) {
		xe::gfx::MeshSubset *subset = mesh->getSubset(i);
		assert(subset);

		driver->setMaterial(subset->getMaterial());
		driver->setMeshSubset(subset);
		driver->render(subset->getPrimitive(), 0);
	}
}

xe::Matrix4f AssetRenderer::computeProjViewModel() const {
	return proj * view * model;
}

void AssetRenderer::setModel(const xe::Matrix4f &transformation) {
	// set the current transformation matrix
	model = transformation;
}
