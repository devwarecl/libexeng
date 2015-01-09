
#include "RayTracerApp.hpp"

#include <algorithm>
#include <cassert>
#include <cfloat>
#include <stdexcept>
#include <cstdint>
#include <list>
#include <array>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/trivial.hpp>

#include <exeng.raytracer/samplers/JitteredSampler.hpp>
#include <exeng.raytracer/tracers/MultiHardwareTracer.hpp>
#include <exeng.raytracer/tracers/HardwareTracer.hpp>
#include <exeng.raytracer/tracers/SoftwareTracer.hpp>
#include <exeng.main/Main.hpp>

#if defined(EXENG_UNIX)
#  include <unistd.h>
#endif

#include <exeng/graphics/Material.hpp>
#include <exeng/scenegraph/TSolidGeometry.hpp>

void displayCurrentPath() {
#if defined(EXENG_UNIX)
	char buffer[1024] = {0};
	::getcwd(buffer, 1024);
	std::cout << "Working directory: " << buffer << std::endl;
#endif
}

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
     * @brief Create a texture with a default color
     */
    std::unique_ptr<Texture> RayTracerApp::createTexture(GraphicsDriver *driver, const Vector3f& size, const Vector4f &color) {
        std::unique_ptr<Texture> texture = driver->createTexture(TextureType::Tex2D, size, ColorFormat::getColorFormatR8G8B8A8());
        
		typedef Vector<std::uint8_t, 4> Vector4ub;

        Vector4ub *textureData = reinterpret_cast<Vector4ub*>(texture->lock());
        for (int i=0; i<size.x * size.y; ++i) {
			textureData[i] = static_cast<Vector4ub>(color * Vector4f(255.0f, 255.0f, 255.0f, 255.0f));
        }
        texture->unlock();

        return texture;
    }
    
    void RayTracerApp::initialize(int argc, char **argv) {

		boost::log::add_file_log (
			boost::log::keywords::file_name="raytracer.%N.log",
			boost::log::keywords::rotation_size = 10*1024*1024
		);

		BOOST_LOG_TRIVIAL(trace) << "Initializing application...";

        // Initialize the exeng root class and plugins.
		BOOST_LOG_TRIVIAL(trace) << "Loading plugins...";

        std::string path = getPluginPath();
        this->getRoot()->getPluginManager()->load("exeng.graphics.gl3", path);
        
        // initialize the gl3 driver, in windowed mode
		BOOST_LOG_TRIVIAL(trace) << "Initializing graphics driver...";
        this->driver = std::unique_ptr<GraphicsDriver>(this->getRoot()->getGraphicsManager()->createDriver());
        this->driver->addEventHandler(this);
        this->driver->initialize();

		BOOST_LOG_TRIVIAL(trace) << "Initializing base objects of the graphics subsystem...";

        DisplayMode mode = this->driver->getDisplayMode();
        
        // create the geometry (a single triangle)
        Vertex2D screenVertices[] = {
            {{-1.0f,  1.0f, 0.0f}, {0.0f,  1.0f}},
            {{ 1.0f,  1.0f, 0.0f}, {1.0f,  1.0f}},
            {{-1.0f, -1.0f, 0.0f}, {0.0f,  0.0f}},
            {{ 1.0f, -1.0f, 0.0f}, {1.0f,  0.0f}}
        };

        VertexFormat screenVertexFormat = VertexFormat::makeVertex2D();

        auto vertexBuffer = std::unique_ptr<Buffer>(this->driver->createVertexBuffer(4*screenVertexFormat.getSize(), screenVertices));

        std::vector<std::unique_ptr<Buffer>> vertexBuffers;
        vertexBuffers.push_back(std::move(vertexBuffer));

        this->screenMeshSubset = std::unique_ptr<MeshSubset>(this->driver->createMeshSubset(std::move(vertexBuffers), screenVertexFormat));
        
        // Initialize the scene.
        this->sceneLoader = std::unique_ptr<SceneLoader>(new SceneLoader(this->driver.get(), this->getRoot()->getMeshManager()));
        this->loadScene();
        this->scene->setBackColor(Color(0.0f, 0.0f, 0.0f, 1.0f));

        // Create the tracer before the render target texture AND the scene.
        this->sampler = std::unique_ptr<Sampler>(new JitteredSampler(25));
        this->sampler->generateSamples();
        
        // this->tracer.reset(new raytracer::tracers::SoftwareTracer(this->scene.get(), this->sampler.get()));
        // this->tracer = std::unique_ptr<Tracer>(new raytracer::tracers::HardwareTracer(this->scene.get(), this->sampler.get()));
		this->tracer = std::unique_ptr<Tracer>(new raytracer::tracers::MultiHardwareTracer(this->scene.get(), this->sampler.get()));
        
        // Create a base texture.
        this->screenTexture = this->createTexture (
            this->driver.get(), 
            {(float)mode.size.width, (float)mode.size.height},
            {0.0f, 0.5f, 1.0f, 1.0f}
        );
        
        this->tracer->setRenderTarget(screenTexture.get());
        
        this->screenMaterial = std::unique_ptr<Material>(new Material());
        this->screenMaterial->getLayer(0)->setTexture(screenTexture.get());
        
        this->camera.setLookAt({0.0f, 0.0f, 0.0f});
        this->camera.setPosition({0.0f, 0.0f, -1.0f});
        this->camera.setUp({0.0f, 1.0f, 0.0f});

		BOOST_LOG_TRIVIAL(trace) << "Application initialization done.";
    }
    
    void RayTracerApp::pollEvents() {
        this->driver->pollEvents();
    }
    
    ApplicationStatus::Enum RayTracerApp::getStatus() const {
        return this->applicationStatus;
    }
    
    void RayTracerApp::update(double seconds) {
        // Actualizar los cuadros por segundo
        /*
        this->frameCounter.update(seconds);
        if (frameCounter.overflow()) {
            std::cout << this->frameCounter.getCurrentFps() << std::endl;
        }
        */
        
        Vector3f delta(0.0f);
        const float moveSpeed = 1.5f;
        const float rotationSpeed = 60.0f;
        
        Vector3f direction = normalize(this->camera.getLookAt() - this->camera.getPosition());
		
        float displace = 0.0f;
        float rotate = 0.0f;

        float displaceDelta = moveSpeed * static_cast<float>(seconds);
        float rotateDelta = rotationSpeed * static_cast<float>(seconds);
        
        // actualiza la camara en funcion de la entrada por teclado
        if (this->buttonStatus[ButtonCode::KeyEsc]) {
            this->applicationStatus = ApplicationStatus::Terminated;
        }
        
        if (this->buttonStatus[ButtonCode::KeyUp]) {
            displace = displaceDelta;
        }

        if (this->buttonStatus[ButtonCode::KeyDown]) {
            displace = -displaceDelta;
        }
        
        if (this->buttonStatus[ButtonCode::KeyLeft]) {
            rotate = -rotateDelta;
        }

        if (this->buttonStatus[ButtonCode::KeyRight]) {
            rotate = rotateDelta;
        }
        
        Matrix4f rotationMatrix = makeRotationMatrix<float>(toRad(rotate), this->camera.getUp());
        
        direction = transform(rotationMatrix, direction);
        
        // rotationMatrix.identity();
        // rotationMatrix.rotation(this->camera.getUp(), rotate);
        // direction = rotationMatrix * direction;
        
        Vector3f position = this->camera.getPosition() + (displace * direction);
        Vector3f lookAt = this->camera.getPosition() + (10.0f * direction);

        this->camera.setOrientation(position, lookAt);
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
        this->driver->beginFrame({0.0f, 0.0f, 0.0f, 1.0f}, ClearFlags::Color | ClearFlags::Depth);
    }
    
    void RayTracerApp::present() {
        this->driver->setMaterial(this->screenMaterial.get());
        this->driver->setMeshSubset( this->screenMeshSubset.get());
        this->driver->render(Primitive::TriangleStrip, 4);
        this->driver->endFrame();
    }
    
    void RayTracerApp::loadScene() {
        this->scene = this->sceneLoader->loadScene("scene.xml");
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
#  include <Windows.h>
#endif

void showMsgBox(const std::string &msg, const std::string &title) {
#if defined(EXENG_WINDOWS)
    ::MessageBox(NULL, msg.c_str(), title.c_str(), MB_OK | MB_ICONERROR);
#else
    std::cout << "[" << title << "] " << std::endl << msg << std::endl;
#endif
}

namespace exeng { namespace main {
    using namespace exeng;
    using namespace exeng::framework;
    using namespace exeng::input;
    using namespace exeng::graphics;

	int main(int argc, char **argv) {
        // TestApp app;
        // app.run();
        // return app.getExitCode();

		using namespace raytracer;
        using namespace exeng;
        using namespace exeng::framework;

        int exitCode = 1;

        try {
            exitCode = Application::execute<RayTracerApp>(argc, argv);
        } catch (std::exception &exp) {
            showMsgBox(exp.what(), "Runtime error");
        }

        return exitCode;
	}
}}
