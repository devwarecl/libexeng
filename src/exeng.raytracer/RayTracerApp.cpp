
#include <exeng.raytracer/RayTracerApp.hpp>
#include <exeng.raytracer/samplers/JitteredSampler.hpp>
#include <exeng.raytracer/tracers/SoftwareTracer.hpp>
#include <exeng.main/Main.hpp>

#include <algorithm>
#include <cassert>
#include <cfloat>
#include <stdexcept>
#include <cstdint>
#include <list>
#include <array>

#include <exeng/graphics/HeapVertexBuffer.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/scenegraph/TSolidGeometry.hpp>

namespace raytracer {
    
    using namespace exeng;
    using namespace exeng::math;
    using namespace exeng::scenegraph;
    using namespace exeng::graphics;
    using namespace exeng::framework;
    using namespace exeng::input;
    
    using namespace raytracer::samplers;
    
    RayTracerApp::RayTracerApp() {
        this->applicationStatus = ApplicationStatus::Running;
        this->lastTime = Timer::getTime();
        
        for (int i=0; i<ButtonCode::Count; ++i) {
            this->buttonStatus[i] = ButtonStatus::Release;
        }
    }
    
    
    RayTracerApp::~RayTracerApp() {
        this->terminate();
    }
    
    
    void RayTracerApp::initialize(int argc, char **argv) {
        // Initialize the exeng root class and plugins.
        std::string path;
    
#ifdef EXENG_WINDOWS
#  ifdef EXENG_DEBUG
        path = "../../bin/Debug/";
#  else
        path = "../../bin/Release/";
#  endif
#else 
        path = "../exeng.graphics.gl3/";
#endif
        
        this->getRoot()->getPluginManager()->load("exeng.graphics.gl3", path);
        
        // initialize the gl3 driver, in windowed mode
        this->driver.reset(this->getRoot()->getGraphicsManager()->createDriver());
        this->driver->addEventHandler(this);
        
        this->driver->initialize();
        DisplayMode mode = this->driver->getDisplayMode();
        
        // create the geometry (a single triangle)
        auto vertexBuffer = this->driver->createVertexBuffer(VertexFormat::makeVertex2D(), 4);
        {        
            VertexArray<Vertex2D> array(vertexBuffer);
            
            array[0].coord = Vector3f(-1.0f,  1.0f, 0.0f);
            array[0].texCoord = Vector2f(0.0f,  1.0f);
            
            array[1].coord = Vector3f( 1.0f,  1.0f, 0.0f);
            array[1].texCoord = Vector2f(1.0f,  1.0f);
            
            array[2].coord = Vector3f(-1.0f, -1.0f, 0.0f);
            array[2].texCoord = Vector2f(0.0f,  0.0f);
            
            array[3].coord = Vector3f( 1.0f, -1.0f, 0.0f);
            array[3].texCoord = Vector2f(1.0f,  0.0f);
        }
        this->vertexBuffer.reset(vertexBuffer);
        
        // create a texture for the render targets
        auto texture = this->driver->createTexture(
            TextureType::Tex2D, 
            Vector3f(static_cast<float>(mode.size.width), 
            static_cast<float>(mode.size.height)), 
            ColorFormat::getColorFormatR8G8B8A8()
        );
        
        struct Texel {
            std::uint8_t red;
            std::uint8_t green;
            std::uint8_t blue;
            std::uint8_t alpha;
        };
        
        Texel *textureData = reinterpret_cast<Texel*>(texture->lock());
        for (int i=0; i<mode.size.width * mode.size.height; ++i) {
            textureData[i].red      = 255;
            textureData[i].green    = 255;
            textureData[i].blue     = 255;
            textureData[i].alpha    = 255;
        }
        texture->unlock();
        
        this->texture.reset(texture);
        
        this->material.reset( new exeng::graphics::Material() );
        this->material->getLayer(0)->setTexture(texture);
        
        this->sampler.reset(new JitteredSampler(25));
        this->sampler->generateSamples();
        
        this->scene.reset(new Scene());
        this->scene->setBackColor(Color(0.0f, 0.0f, 0.0f, 1.0f));
        
        this->loadScene();
        
        this->camera.reset( new Camera() );
        this->camera->setLookAt(Vector3f(0.0f, 0.0f, 0.0f));
        this->camera->setPosition(Vector3f(0.0f, 2.0f, -75.0f));
        this->camera->setUp(Vector3f(0.0f, 1.0f, 0.0f));
        
        // this->tracer.reset(new raytracer::tracers::SoftwareTracer(this->texture.get(), this->scene.get(), this->sampler.get()));
        this->tracer.reset(new raytracer::tracers::SoftwareTracer(this->texture.get(), this->scene.get(), nullptr));
    }
    
    
    void RayTracerApp::pollEvents() {
        this->driver->pollEvents();
    }
    
    
    ApplicationStatus::Enum RayTracerApp::getStatus() const {
        return this->applicationStatus;
    }
    
    
    void RayTracerApp::update(double seconds) {
        // Actualizar los cuadros por segundo
        this->frameCounter.update(seconds);
        std::cout << this->frameCounter.getCurrentFps() << std::endl;
        
        // actualiza la camara en funcion de la entrada por teclado
        if (this->buttonStatus[ButtonCode::KeyEsc]) {
            this->applicationStatus = ApplicationStatus::Terminated;
        }
    
        if (this->buttonStatus[ButtonCode::KeyUp]) {
            auto cameraPosition = this->camera->getPosition();
            cameraPosition.z += 2.5f;
            this->camera->setPosition(cameraPosition);
        }
    
        if (this->buttonStatus[ButtonCode::KeyDown]) {
            auto cameraPosition = this->camera->getPosition();
            cameraPosition.z -= 2.5f;
            this->camera->setPosition(cameraPosition);
        }
    
        if (this->buttonStatus[ButtonCode::KeyRight]) {
            auto cameraPosition = this->camera->getPosition();
            cameraPosition.x += 2.5f;
            this->camera->setPosition(cameraPosition);
        }
    
        if (this->buttonStatus[ButtonCode::KeyLeft]) {
            auto cameraPosition = this->camera->getPosition();
            cameraPosition.x -= 2.5f;
            this->camera->setPosition(cameraPosition);
        }
    }
    
    void RayTracerApp::render() {
        this->clear();
        this->tracer->render(this->camera.get());
        this->present();
    }
    
    int RayTracerApp::getExitCode() const {
        return 0;
    }
    
    
    void RayTracerApp::terminate() {
        this->driver->terminate();
    }
    
    
    void RayTracerApp::clear() {
        this->driver->beginFrame(Color(0.0f, 0.0f, 0.0f, 1.0f));
    }
    
    
    void RayTracerApp::present() {
        this->driver->setMaterial(this->material.get());
        this->driver->setVertexBuffer(this->vertexBuffer.get());
        this->driver->render(Primitive::TriangleStrip, 4);
        this->driver->endFrame();
    }
    
    
    void RayTracerApp::loadScene() {
        this->scene.reset( this->sceneLoader.loadScene("scene.xml") );
    }
    
    
    void RayTracerApp::handleEvent(const EventData &data) {
        if (data.eventType == TypeId<InputEventData>()) {
            const InputEventData &inputEventData = data.cast<InputEventData>();
            this->buttonStatus[ inputEventData.buttonCode ] = inputEventData.buttonStatus;
        } else if (data.eventType == TypeId<CloseEventData>()) {
            this->applicationStatus = ApplicationStatus::Terminated;
        }
    }
}


namespace exeng { namespace main {
	int main(int argc, char **argv) {
        return exeng::framework::Application::execute<raytracer::RayTracerApp>(argc, argv);
	}
}}
