
#include "RasterRenderer.hpp"

#include <xe/gfx/Mesh.hpp>
#include <xe/sg/Light.hpp>
#include <xe/sg/Camera.hpp>

RasterRenderer::RasterRenderer(xe::gfx::GraphicsDriver *driver_) : driver(driver_) {
	assert(driver);

	programmableModule = driver->getModernModule();

	assert(programmableModule);
	assert(programmableModule->getShaderProgram());
}

void RasterRenderer::beginFrame(const xe::Vector4f &color) {
	// std::cout << "RasterRenderer::beginFrame()" << std::endl;

	driver->beginFrame(color);
}

void RasterRenderer::endFrame() {
	// std::cout << "RasterRenderer::endFrame()" << std::endl;
	// std::cout << std::endl;

	driver->endFrame();
}

void RasterRenderer::render(xe::sg::Light *light) {
	assert(light);

	// std::cout << "RasterRenderer::render(Light)" << std::endl;

	programmableModule->setProgramParam("light_position", light->getPosition());
	programmableModule->setProgramParam("light_range", light->getRange());
}

void RasterRenderer::render(xe::sg::Camera *camera) {
	assert(camera);

	// std::cout << "RasterRenderer::render(Camera)" << std::endl;

	// driver->setViewport(camera->getViewport());
	
	xe::Matrix4f proj = camera->computeProj();
	xe::Matrix4f view = camera->computeView();

	// std::cout << proj << std::endl;
	// std::cout << view << std::endl;

	programmableModule->setProgramMatrix("proj", proj);
	programmableModule->setProgramMatrix("view", view);
}

void RasterRenderer::render(xe::sg::Geometry *geometry) {
	assert(geometry);
}

void RasterRenderer::render(xe::gfx::Mesh *mesh) {
	assert(mesh);

	// std::cout << "RasterRenderer::render(Mesh)" << std::endl;
	
	driver->render(mesh);
}

void RasterRenderer::setModel(const xe::Matrix4f &transformation) {
	// std::cout << "RasterRenderer::setModel()" << std::endl;
	// std::cout << transformation << std::endl;

	programmableModule->setProgramMatrix("model", transformation);
}
