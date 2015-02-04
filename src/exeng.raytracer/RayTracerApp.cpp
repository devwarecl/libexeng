
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
    
	class RotateSceneNodeAnimator : public SceneNodeAnimator {
	public:
		virtual void animateNode(const float seconds, SceneNode *node) override
		{
			const float rotationSpeed = 180.0f;

			angle += seconds * rotationSpeed;
			if (angle >= 360.0f) {
				angle = std::fmod(angle, 360.0f);
			}

			Matrix4f transform = rotatey(exeng::rad(angle));

			node->setTransform(transform);
		}

	private:
		float angle = 0.0f;
	};

	/**
	 * @brief Moves the scene node along the X axis
	 */
	class TranslateSceneNodeAnimator : public SceneNodeAnimator {
	public:
		virtual void animateNode(const float seconds, SceneNode *node) override
		{
			this->position.x += direction * seconds * speed;

			if (this->position.x > 5.0f) {
				direction = -1.0f;
			}

			if (this->position.x < -5.0f) {
				direction = 1.0f;
			}

			Matrix4f transform = translate(this->position);
			node->setTransform(transform);
		}
	
	private:
		const float speed = 0.125f;
		float direction = 1.0f;

		Vector3f position = {0.0f, 0.0f, 0.0f};
	};

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
		// Material
		std::vector<MaterialAttrib> attribs = {
			{"ambient", DataType::Float32, 4},
			{"diffuse", DataType::Float32, 4},
			{"specular", DataType::Float32, 4},
			{"ambient", DataType::Float32, 1}
		};

		this->materialFormat = MaterialFormat(attribs);

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
        Vertex2 screenVertices[] = {
            {{-1.0f,  1.0f, 0.0f}, {0.0f,  1.0f}},
            {{ 1.0f,  1.0f, 0.0f}, {1.0f,  1.0f}},
            {{-1.0f, -1.0f, 0.0f}, {0.0f,  0.0f}},
            {{ 1.0f, -1.0f, 0.0f}, {1.0f,  0.0f}}
        };

        VertexFormat screenVertexFormat = Vertex2::format();

        auto vertexBuffer = this->driver->createVertexBuffer(4*screenVertexFormat.getSize(), screenVertices);

        std::vector<std::unique_ptr<Buffer>> vertexBuffers;
        vertexBuffers.push_back(std::move(vertexBuffer));

        this->screenMeshSubset = this->driver->createMeshSubset(std::move(vertexBuffers), screenVertexFormat);
        
        // Initialize the scene.
        this->sceneLoader = std::unique_ptr<SceneLoader>(new SceneLoader(this->driver.get(), this->getRoot()->getMeshManager()));
        this->loadScene();
        this->scene->setBackColor({0.0f, 0.0f, 0.0f, 1.0f});
        
        // Create the tracer before the render target texture AND the scene.
        this->sampler = std::unique_ptr<Sampler>(new JitteredSampler(25));
        this->sampler->generateSamples();
        
        // this->tracer.reset(new raytracer::tracers::SoftwareTracer(this->scene.get(), this->sampler.get()));
        // this->tracer = std::unique_ptr<Tracer>(new raytracer::tracers::HardwareTracer(this->scene.get(), this->sampler.get()));
		this->tracer = this->tracerFactory.createTracer(this->scene.get(), this->sampler.get());
        
        // Create a base texture.
        this->screenTexture = this->createTexture (
            this->driver.get(), 
            {(float)mode.size.width, (float)mode.size.height},
            {0.0f, 0.5f, 1.0f, 1.0f}
        );
        
        this->tracer->setRenderTarget(screenTexture.get());
        
        this->screenMaterial = std::unique_ptr<Material>(new Material(&this->materialFormat));
        this->screenMaterial->getLayer(0)->setTexture(screenTexture.get());
        
        this->camera.setLookAt({0.0f, 0.0f, 0.0f});
        this->camera.setPosition({0.0f, 0.0f, -1.0f});
        this->camera.setUp({0.0f, 1.0f, 0.0f});

		// attach a rotation animator to the central cube
		auto animator = std::unique_ptr<SceneNodeAnimator>(new RotateSceneNodeAnimator());
		// auto animator = std::unique_ptr<SceneNodeAnimator>(new TranslateSceneNodeAnimator());

		this->animators[this->scene->getRootNode()->getChild("boxNode3")] = std::move(animator);

		this->defaultMaterial = std::unique_ptr<Material>(new Material(&this->materialFormat));
		this->driver->setDefaultMaterial(this->defaultMaterial.get());

		BOOST_LOG_TRIVIAL(trace) << "Application initialization done.";
    }
    
    void RayTracerApp::pollEvents() {
        this->driver->pollEvents();
    }
    
    ApplicationStatus::Enum RayTracerApp::getStatus() const {
        return this->applicationStatus;
    }
    
    void RayTracerApp::update(double seconds) {
		// Animate the scene nodes
		for (auto it=this->animators.begin(); it!=this->animators.end(); ++it) {
			it->second->animateNode(float(seconds), it->first);
		}

		// camera update
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
        
        Matrix4f rotationMatrix = exeng::rotate<float>(rad(rotate), this->camera.getUp());
        
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
        this->scene = this->sceneLoader->loadScene("scene.xml", this->materialFormat);
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

	int main(int argc, char **argv) 
	{
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
