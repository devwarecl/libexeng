
#include "ComputeInteropApp.hpp"

#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/MeshManager.hpp>
#include <xe/gfx/TextureManager.hpp>
#include <xe/gfx/MaterialLibraryImpl.hpp>
#include <xe/gfx/MeshSubsetGeneratorBox.hpp>
#include <xe/sg/SceneRendererGeneric.hpp>
#include <xe/cm/ComputeManager.hpp>

ComputeInteropApp::ComputeInteropApp() {}

ComputeInteropApp::~ComputeInteropApp() {}

void ComputeInteropApp::initialize() {

	textureManager = this->getGraphicsManager()->getTextureManager();
	meshManager = this->getGraphicsManager()->getMeshManager();

	// intialize graphics driver
	graphicsDriver = this->createGraphicsDriver();
	graphicsDriver->initialize();

	// get input management interfaces
	inputManager = graphicsDriver->getInputManager();
	keyboardStatus = inputManager->getKeyboard()->getStatus();

	// create renderer pipeline
	renderer = std::make_unique<PhongRenderer>(graphicsDriver.get());

	// create material library
	materialLibrary = std::make_unique<xe::gfx::MaterialLibraryImpl>(*renderer->getMaterialFormat());
	
	// create scene renderer
	sceneRenderer = std::make_unique<xe::sg::SceneRendererGeneric>(renderer.get());

	// attach
	textureManager->setGraphicsDriver(graphicsDriver.get());
	meshManager->setGraphicsDriver(graphicsDriver.get());
	meshManager->setMaterialLibrary(materialLibrary.get());
	
	// generate sample scene
	scene = this->createScene();

	// attach the scene to the scene renderer
	sceneRenderer->setScene(scene.get());

	// create the Mesh Manipulator
	meshManipulator = std::make_unique<MeshManipulator>(this->getComputeManager()->createComputeModule(), graphicsDriver.get());

	running = true;
}

void ComputeInteropApp::terminate() {
	this->getGraphicsManager()->getMeshManager()->cleanup();
	textureManager->cleanup();
}

void ComputeInteropApp::doEvents() {
	inputManager->poll();
}

void ComputeInteropApp::update(const float seconds) {
	const float speed = 10.0f * seconds;
	std::cout << speed << std::endl;
	// check if the user wants to leave the demo
	running = keyboardStatus->isKeyReleased(xe::input2::KeyCode::KeyEsc);

	// update camera position
	camera.lookat.y = 0.25f;
	camera.position.y = 0.25f;

	if (keyboardStatus->isKeyPressed(xe::input2::KeyCode::KeyLeft)) {
		camera.lookat.x -= speed;
		camera.position.x -= speed;
	}

	if (keyboardStatus->isKeyPressed(xe::input2::KeyCode::KeyRight)) {
		camera.lookat.x += speed;
		camera.position.x += speed;
	}

	if (keyboardStatus->isKeyPressed(xe::input2::KeyCode::KeyUp)) {
		camera.lookat.z -= speed;
		camera.position.z -= speed;
	}

	if (keyboardStatus->isKeyPressed(xe::input2::KeyCode::KeyDown)) {
		camera.lookat.z += speed;
		camera.position.z += speed;
	}
}

void ComputeInteropApp::render() {
	sceneRenderer->renderScene();
}

bool ComputeInteropApp::isRunning() const {
	return running;
}

xe::gfx::GraphicsDriverPtr ComputeInteropApp::createGraphicsDriver() {
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

xe::sg::ScenePtr ComputeInteropApp::createScene() {
	auto scene = std::make_unique<xe::sg::Scene>();

	scene->setBackColor({0.2f, 0.2f, 0.8f, 1.0f});
	scene->getRootNode()->setRenderable(&camera);

	// setup box generator
	xe::gfx::MeshSubsetGeneratorBox generator(graphicsDriver.get());

	// generate texture
	xe::gfx::Texture *texture = textureManager->generateCheckerboard (
		"texture", 
		xe::Vector2i(64, 64), 
		xe::Vector2i(8, 8)
	);

	// generate material
	xe::gfx::Material *material = materialLibrary->createMaterial();

	material->setAttribute("diffuse", xe::Vector4f(0.8f, 0.8f, 0.8f, 1.0f));
	material->getLayer(0)->setTexture(texture);

	// generate box subset
	auto subset = generator.generate({renderer->getVertexFormat()});
	subset->setMaterial(material);

	// generate the box mesh
	xe::sg::SceneNode *node = scene->getRootNode();

	xe::gfx::Mesh *mesh = meshManager->getMesh("boxMesh", std::make_unique<xe::gfx::Mesh>(std::move(subset)));

	float values[] = {-2.0f, 0.0f, 2.0f};

	for (float value1 : values) {
		for (float value2 : values) {
			node->addChild(xe::translate<float>(xe::Vector3f(value1, 0.0f, value2)), mesh);
		}
	}

	return scene;
}
