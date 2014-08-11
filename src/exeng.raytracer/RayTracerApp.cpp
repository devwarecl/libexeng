
#include <exeng.raytracer/RayTracerApp.hpp>
#include <exeng.raytracer/samplers/JitteredSampler.hpp>
#include <exeng.raytracer/tracers/HardwareTracer.hpp>
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

/**
 * @brief Get the path where the interface implementations are located.
 */
std::string getPluginPath() {
#ifdef EXENG_WINDOWS
#  ifdef EXENG_DEBUG
    return "../../bin/Debug/";
#  else
    return "../../bin/Release/";
#  endif
#else 
    return "../exeng.graphics.gl3/";
#endif
}

namespace raytracer {
    using namespace exeng;
    using namespace exeng::math;
    using namespace exeng::scenegraph;
    using namespace exeng::graphics;
    using namespace exeng::framework;
    using namespace exeng::input;
    using namespace raytracer::samplers;
    using namespace raytracer::tracers;
    
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
    
    /**
     * Create a texture with a default color
     */
    Texture* RayTracerApp::createTexture(GraphicsDriver *driver, const Vector3f& size, const Vector4f &color) {
        Texture *texture = driver->createTexture(TextureType::Tex2D, size, ColorFormat::getColorFormatR8G8B8A8());
        
        struct Texel { std::uint8_t red, green, blue, alpha; };
        
        Texel *textureData = reinterpret_cast<Texel*>(texture->lock());
        for (int i=0; i<size.x * size.y; ++i) {
            textureData[i] = {
                static_cast<std::uint8_t>(color.x * 255), 
                static_cast<std::uint8_t>(color.y * 255), 
                static_cast<std::uint8_t>(color.z * 255), 
                static_cast<std::uint8_t>(color.w * 255)
            };
        }
        texture->unlock();

        return texture;
    }

    void RayTracerApp::initialize(int argc, char **argv) {
        // Initialize the exeng root class and plugins.
        std::string path = getPluginPath();
        
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

            array[0] = {{-1.0f,  1.0f, 0.0f}, {0.0f,  1.0f}};
            array[1] = {{ 1.0f,  1.0f, 0.0f}, {1.0f,  1.0f}};
            array[2] = {{-1.0f, -1.0f, 0.0f}, {0.0f,  0.0f}};
            array[3] = {{ 1.0f, -1.0f, 0.0f}, {1.0f,  0.0f}};
        }
        this->vertexBuffer.reset(vertexBuffer);
        
        // Initialize the scene.
        this->loadScene();
        this->scene->setBackColor(Color(0.0f, 0.0f, 0.0f, 1.0f));

        // Create the tracer before the render target texture AND the scene.
        this->sampler.reset(new JitteredSampler(25));
        this->sampler->generateSamples();

        // this->tracer.reset(new raytracer::tracers::SoftwareTracer(this->scene.get(), this->sampler.get()));
        Tracer *tracer = new raytracer::tracers::HardwareTracer(this->scene.get(), this->sampler.get());
        this->tracer.reset(tracer);
        
        // Create a base texture.
        Texture *texture = this->createTexture (
            this->driver.get(), 
            {static_cast<float>(mode.size.width), static_cast<float>(mode.size.height)},
            {0.0f, 0.5f, 1.0f, 1.0f}
        );

        this->texture.reset(texture);
        this->tracer->setRenderTarget(texture);
        
        this->material.getLayer(0)->setTexture(texture);
        
        this->camera.setLookAt({0.0f, 0.0f, 0.0f});
        this->camera.setPosition({0.0f, 2.0f, -75.0f});
        this->camera.setUp({0.0f, 1.0f, 0.0f});
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
            auto cameraPosition = this->camera.getPosition();
            cameraPosition.z += 2.5f;
            this->camera.setPosition(cameraPosition);
        }
    
        if (this->buttonStatus[ButtonCode::KeyDown]) {
            auto cameraPosition = this->camera.getPosition();
            cameraPosition.z -= 2.5f;
            this->camera.setPosition(cameraPosition);
        }
    
        if (this->buttonStatus[ButtonCode::KeyRight]) {
            auto cameraPosition = this->camera.getPosition();
            cameraPosition.x += 2.5f;
            this->camera.setPosition(cameraPosition);
        }
    
        if (this->buttonStatus[ButtonCode::KeyLeft]) {
            auto cameraPosition = this->camera.getPosition();
            cameraPosition.x -= 2.5f;
            this->camera.setPosition(cameraPosition);
        }
    }
    
    void RayTracerApp::render() {
        this->clear();
        this->tracer->render(&this->camera);
        this->present();
    }
    
    int RayTracerApp::getExitCode() const {
        return 0;
    }
    
    void RayTracerApp::terminate() {
        this->driver->terminate();
    }
    
    void RayTracerApp::clear() {
        this->driver->beginFrame({0.0f, 0.0f, 0.0f, 1.0f});
    }
    
    void RayTracerApp::present() {
        this->driver->setMaterial(&this->material);
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


#if defined(EXENG_WINDOWS)
#include <Windows.h>
#endif

void showMsgBox(const std::string &msg, const std::string &title) {
#if defined(EXENG_WINDOWS)
    ::MessageBox(NULL, msg.c_str(), title.c_str(), MB_OK | MB_ICONERROR);
#else
    std::cout << exp.what() << std::endl;
#endif
}

namespace exeng { namespace main {
	int main(int argc, char **argv) {
        using namespace raytracer;
        using namespace exeng;
        using namespace exeng::framework;

        int exitCode = -1;

        try {
            exitCode = Application::execute<RayTracerApp>(argc, argv);
        } catch (std::exception &exp) {
            showMsgBox(exp.what(), "Runtime error");
        }

        return exitCode;
	}
}}
