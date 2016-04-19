
#include "DemoApp.hpp"
#include "PhongPipeline.hpp"

#include <xe/gfx/GraphicsManager.hpp>

namespace xe {

    void DemoApp::initialize() {
        graphicsDriver = this->getGraphicsManager()->createDriver();
        graphicsDriver->initialize();
        
        keyboard = graphicsDriver->getInputManager()->getKeyboard();
        
        pipeline = std::make_unique<xe::sg::PhongPipeline>(graphicsDriver.get());
        renderer = std::make_unique<xe::sg::SceneRendererGeneric>(pipeline.get());
        
        this->initializeScene();
        
        renderer->setScene(&scene);
        
        running = true;
    }
    
    void DemoApp::initializeScene() {
        scene.setBackColor({0.2f, 0.2f, 0.8f, 1.0f});
    }
    
    void DemoApp::terminate() {}
    
    void DemoApp::doEvents() {
        xe::input2::KeyboardStatus *keyStatus = keyboard->getStatus();
        
        graphicsDriver->getInputManager()->poll();
        
        running = !keyStatus->isKeyPopped(xe::input2::KeyCode::KeyEsc);
        
    }
    
    void DemoApp::update(const float seconds) {
        
    }
    
    void DemoApp::render() {
        renderer->renderScene();
    }
    
    int main(int argc, char** argv) {
		return xe::Application::execute<xe::DemoApp>(argc, argv);
	}
}
