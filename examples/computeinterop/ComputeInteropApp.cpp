
#include "ComputeInteropApp.hpp"
#include "PhongRenderer.hpp"

#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/MeshManager.hpp>
#include <xe/gfx/TextureManager.hpp>
#include <xe/gfx/MaterialLibraryImpl.hpp>
#include <xe/sg/SceneRendererGeneric.hpp>

ComputeInteropApplication::ComputeInteropApplication() {}

ComputeInteropApplication::~ComputeInteropApplication() {}

void ComputeInteropApplication::initialize() {
	
	// intialize graphics driver
	graphicsDriver = this->createGraphicsDriver();
	graphicsDriver->initialize();

	// get input management interfaces
	inputManager = graphicsDriver->getInputManager();
	keyboardStatus = inputManager->getKeyboard()->getStatus();

	// create renderer pipeline
	renderer = std::make_unique<PhongRenderer>(graphicsDriver.get());

	// create material library
	materialLibrary = std::make_unique<xe::gfx::MaterialLibraryImpl>();
	
	// create scene renderer
	sceneRenderer = std::make_unique<xe::sg::SceneRendererGeneric>(renderer.get());

	// generate sample scene
	scene = this->createScene();

	// 
	sceneRenderer->setScene(scene.get());
}

void ComputeInteropApplication::terminate() {
	this->getGraphicsManager()->getMeshManager()->cleanup();
	this->getGraphicsManager()->getTextureManager()->cleanup();
}

void ComputeInteropApplication::doEvents() {
	inputManager->poll();
	running = keyboardStatus->isKeyReleased(xe::input2::KeyCode::KeyEsc);
}

void ComputeInteropApplication::update(const float seconds) {}

void ComputeInteropApplication::render() {
	sceneRenderer->renderScene();
}

bool ComputeInteropApplication::isRunning() const {
	return running;
}

xe::gfx::GraphicsDriverPtr ComputeInteropApplication::createGraphicsDriver() {
    // display all available graphics drivers
    auto driverInfos = this->getGraphicsManager()->getAvailableDrivers();

    if (driverInfos.size() == 0) {
        std::cout << "No available graphics drivers!" << std::endl;
        throw std::runtime_error("");
    }
        
    // select the first graphics driver
    std::cout << "Available graphic drivers:" << std::endl;
    for (const auto &driverInfo : driverInfos) {
        std::cout << driverInfo.name << std::endl;
    }

    return this->getGraphicsManager()->createDriver(driverInfos[0]);
}

xe::sg::ScenePtr ComputeInteropApplication::createScene() {

	auto scene = std::make_unique<xe::sg::Scene>();

	scene->setBackColor({0.2f, 0.2f, 0.8f, 1.0f});

	return scene;
}
