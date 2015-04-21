
#include <exeng/Exeng.hpp>
#include <exeng/framework/GraphicsApplication.hpp>

#include "Fragment.glsl.hpp"
#include "Vertex.glsl.hpp"

using namespace exeng;
using namespace exeng::framework;
using namespace exeng::graphics;
using namespace exeng::scenegraph;
using namespace exeng::input;

class SpatialAnimator : public SceneNodeAnimator {
public:
	SpatialAnimator() {}
	explicit SpatialAnimator(SceneNode *node) : SceneNodeAnimator(node) {}

	virtual void update(double seconds) override {
		this->angle += static_cast<float>(60.0 * seconds);

		auto transform = identity<float, 4>();
		transform *= rotatex<float>(rad(angle));
		transform *= rotatey<float>(rad(angle));
		transform *= rotatez<float>(rad(angle));

		this->getSceneNode()->setTransform(transform);
	}

private:
	float angle = 0.0f;
};

/*
class MaterialLibrary {
public:
	explicit MaterialLibrary(GraphicsDriver *driver) {
		this->driver = driver;
		this->format = this->createMaterialFormat();
		this->shaderProgram = this->createShaderProgram();
	}

	Material* createMaterial(const std::string &name) {
		MaterialPtr materialPtr = std::make_unique<Material>(&this->format, name);
		Material *material = materialPtr.get();

		this->materials.push_back(std::move(materialPtr));

		return material;
	}

	Material* getMaterial(const std::string &name) {
		auto materialPos = std::find_if(this->materials.begin(), this->materials.end(), [name](MaterialPtr &material) {
			return material->getName() == name;
		});

		if (materialPos == this->materials.end()) {
			return nullptr;
		}

		return materialPos->get();
	}

private:
	ShaderProgramPtr createShaderProgram() {
		std::string vertexShaderSrc = 
			"#version 330\n"
			"\n"
			"in vec2 uv;\n"
			"out vec4 fragmentColor;\n"
			"uniform sampler2D textureSampler;\n"
			"\n"
			"void main() { \n"
			"	fragmentColor = texture(textureSampler, uv);\n"
			"}\n";

		std::string fragmentShaderSrc = 
			"#version 330\n"
			"\n"
			"uniform mat4 WorldTransform;\n"
			"in vec4 coord;\n"
			"// in vec3 normal;\n"
			"in vec2 texCoord;\n"
			"out vec2 uv;\n"
			"\n"
			"void main() {\n"
			"	gl_position = coord * WorlTransform;\n"
			"	uv = texCoord;\n"
			"}\n";

		return this->driver->getModernModule()->createShaderProgram(vertexShaderSrc, fragmentShaderSrc);
	}

	MaterialFormat createMaterialFormat() {
		return MaterialFormat({ 
			{"ambient", DataType::Float32, 4},
			{"diffuse", DataType::Float32, 4},
			{"specular", DataType::Float32, 4}
		});
	}

private:
	MaterialFormat format;
	ShaderProgramPtr shaderProgram;
	GraphicsDriver *driver = nullptr;

	std::list<MaterialPtr> materials;
};
typedef std::unique_ptr<MaterialLibrary> MaterialLibraryPtr;
*/

class Demo01 : public GraphicsApplication, public IEventHandler {
public:
	std::string getPluginPath() {
#if defined(EXENG_UNIX)
        return "../../plugins/libexeng.graphics.gl3/";
#else
#  if defined (EXENG_DEBUG)
		return "../../bin/Debug/";
#  else 
		return "../../bin/Release/";
#  endif
#endif
	}

	ScenePtr initScene() {
		Mesh *boxMesh = this->getMeshManager()->generateBoxMesh("boxMesh", {0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f});

		ScenePtr scene = std::make_unique<Scene>();
		scene->setBackColor({0.2f, 0.3f, 0.8f, 1.0f});
		scene->createSceneNode("boxSceneNode", boxMesh);

		return scene;
	}

	ShaderProgramPtr initShaderProgram() {
		auto vertexShader = this->graphicsDriver->getModernModule()->createShader(ShaderType::Vertex, vertex_glsl_data, vertex_glsl_size);
		auto fragmentShader = this->graphicsDriver->getModernModule()->createShader(ShaderType::Fragment, fragment_glsl_data, fragment_glsl_size);

		vertexShader->compile();
		fragmentShader->compile();

		ShaderProgramPtr shaderProgram;
		shaderProgram->addShader(std::move(vertexShader));
		shaderProgram->addShader(std::move(fragmentShader));
		shaderProgram->link();

		return shaderProgram;
	}

    virtual void initialize(int argc, char **argv) override {
		this->getPluginManager()->setPluginPath(this->getPluginPath());
        this->getPluginManager()->loadPlugin("exeng.graphics.gl3");
		
        this->graphicsDriver = this->getGraphicsManager()->createDriver();
        this->graphicsDriver->addEventHandler(this);
        this->graphicsDriver->initialize();

		this->getMeshManager()->setGraphicsDriver(this->graphicsDriver.get());

		this->scene = this->initScene();
		this->shaderProgram = this->initShaderProgram();

		this->camera = this->scene->createCamera();
		this->camera->setPosition({0.0f, 2.0f, 4.0f});
		this->camera->setLookAt({0.0f, 0.0f, 0.0f});
		this->camera->setViewport(Rectf((Size2f)this->graphicsDriver->getDisplayMode().size));

		std::unique_ptr<SceneRenderer> sceneRenderer(new GenericSceneRenderer(this->graphicsDriver.get()));

		// this->sceneManager = std::make_unique<SceneManager>(scene);
		this->sceneManager->setSceneRenderer(std::move(sceneRenderer));
		
		//
		Mesh *boxMesh = this->getMeshManager()->generateBoxMesh("boxMesh", {0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f});

		this->scene->createSceneNode("boxSceneNode", boxMesh);

		this->animator = std::make_unique<SpatialAnimator>();
		this->animator->setSceneNode(this->scene->getRootNode()->getChild("boxSceneNode"));
		this->sceneManager->addAnimator(this->animator.get());
    }
    
    virtual ApplicationStatus::Enum getStatus() const override {
        return this->status;
    }
    
    virtual void pollEvents() override {
        this->graphicsDriver->pollEvents();
    }
    
    virtual void update(double seconds) override {
		this->sceneManager->update(seconds);
    }
    
    virtual void render() override {
		this->sceneManager->render(this->camera);
    }
    
    virtual void handleEvent(const EventData &data) override {
        const InputEventData &inputData = data.cast<InputEventData>();
        
        if (inputData.check(ButtonStatus::Press, ButtonCode::KeyEsc)) {
            this->status = ApplicationStatus::Terminated;
        }
    }

private:
    std::unique_ptr<GraphicsDriver> graphicsDriver;
	std::unique_ptr<SceneManager> sceneManager;
	std::unique_ptr<SceneNodeAnimator> animator;
	ShaderProgramPtr shaderProgram;
	ScenePtr scene;

	Camera *camera = nullptr;
    ApplicationStatus::Enum status = ApplicationStatus::Running;
};

int main(int argc, char **argv) {
    return Application::execute<Demo01>(argc, argv);
}
