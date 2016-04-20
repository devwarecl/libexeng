
#include "TetrisApp.hpp"
#include "PhongPipeline.hpp"

#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/MeshSubsetGeneratorBox.hpp>
#include <xe/sg/Camera.hpp>
#include <xe/sg/SceneNode.hpp>

namespace xe {

    void DemoApp::initialize() {
        graphicsDriver = this->getGraphicsManager()->createDriver();
        graphicsDriver->initialize();
        
        keyboard = graphicsDriver->getInputManager()->getKeyboard();
        
        pipeline = std::make_unique<xe::sg::PhongPipeline>(graphicsDriver.get());
        renderer = std::make_unique<xe::sg::SceneRendererGeneric>(pipeline.get());
        
        material1 = this->createMaterial({0.8f, 0.0f, 0.0f, 1.0f});
        material2 = this->createMaterial({0.0f, 0.8f, 0.0f, 1.0f});
        material3 = this->createMaterial({0.0f, 0.0f, 0.8f, 1.0f});
        
        cubeMesh1 = this->createCubeMesh(material1.get());
        cubeMesh2 = this->createCubeMesh(material2.get());
        cubeMesh3 = this->createCubeMesh(material3.get());
        
        scene = this->createScene();
        
        renderer->setScene(scene.get());
        
        running = true;
    }
    
    void DemoApp::terminate() {}
    
    void DemoApp::doEvents() {
        xe::input2::KeyboardStatus *keyStatus = keyboard->getStatus();
        
        graphicsDriver->getInputManager()->poll();
        
        running = !keyStatus->isKeyPopped(xe::input2::KeyCode::KeyEsc);
    }
    
    void DemoApp::update(const float seconds) {}
    
    void DemoApp::render() {
        renderer->renderScene();
    }
    
    xe::sg::ScenePtr DemoApp::createScene() {
        camera.position = {0.0f, 5.0f, 7.5f};
        
        auto scene = std::make_unique<xe::sg::Scene>();
        
        scene->setBackColor({0.2f, 0.2f, 0.2f, 1.0f});
        
        scene->getRootNode()->setRenderable(&camera);
        scene->getRootNode()->addChild(xe::identity<float, 4>(), cubeMesh1.get());
        
        return scene;
    }
    
    xe::gfx::MeshPtr DemoApp::createCubeMesh(xe::gfx::Material *material) {
        xe::gfx::MeshSubsetGeneratorBox generator(graphicsDriver.get());
        
        auto subset = generator.generate({pipeline->getVertexFormat()});
        
        subset->setMaterial(material);
        
        return std::make_unique<xe::gfx::Mesh>(std::move(subset));
    }
    
    xe::gfx::MaterialPtr DemoApp::createMaterial(const xe::Vector4f &color) {
        auto material = std::make_unique<xe::gfx::Material>(pipeline->getMaterialFormat());
        
        material->setAttribute("ambient", color);
        
        return material;
    }
    
    int main(int argc, char** argv) {
		return xe::Application::execute<xe::DemoApp>(argc, argv);
	}
}
