
#include "DemoApp.hpp"
#include "PhongPipeline.hpp"

#include <xe/gfx/GraphicsManager.hpp>

namespace xe {

    void DemoApp::initialize() {
        graphicsDriver = this->getGraphicsManager()->createDriver();
        graphicsDriver->initialize();
        
        keyboard = graphicsDriver->getInputManager()->getKeyboard();
        
        pipeline = std::make_unique<xe::PhongPipeline>(graphicsDriver.get());
        renderer = std::make_unique<xe::sg::SceneRendererGeneric>(pipeline.get());
        renderer->setScene(&scene);
        
        running = true;
    }
    
    void DemoApp::terminate() {
        
    }
    
    void DemoApp::doEvents() {
        xe::input2::KeyboardStatus *keyStatus = keyboard->getStatus();
        
        graphicsDriver->getInputManager()->poll();
        
        if (keyStatus->isKeyPopped(xe::input2::KeyCode::KeyEsc)) {
            running = false;
        }
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
