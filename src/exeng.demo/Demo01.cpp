
#include <exeng/Exeng.hpp>
#include <exeng/framework/GraphicsApplication.hpp>

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
		this->angle += 60.0f * static_cast<float>(seconds);
		auto transform = rotate<float>(rad(angle), {0.0f, 1.0f, 0.0f});

		this->getSceneNode()->setTransform(transform);
	}

private:
	float angle = 0.0f;
};

class Demo01 : public GraphicsApplication, public IEventHandler {
public:
    virtual void initialize(int argc, char **argv) override 
    {
		std::string pluginPath = "";

#if defined(EXENG_UNIX)
        pluginPath = "../../plugins/libexeng.graphics.gl3/";
#else
#  if defined (EXENG_DEBUG)
		pluginPath = "../../bin/Debug/";
#  else 
		pluginPath = "../../bin/Release/";
#  endif
#endif
		this->materialFormat = MaterialFormat({ 
			{"ambient", DataType::Float32, 4}, 
			{"diffuse", DataType::Float32, 4}, 
			{"specular", DataType::Float32, 4}
		});

		this->material = std::make_unique<Material>(&this->materialFormat);

		this->getPluginManager()->setPluginPath(pluginPath);
        this->getPluginManager()->loadPlugin("exeng.graphics.gl3");
		
        this->graphicsDriver = this->getGraphicsManager()->createDriver();
        this->graphicsDriver->addEventHandler(this);
        this->graphicsDriver->initialize();
		this->graphicsDriver->setDefaultMaterial(this->material.get());

		auto scene = std::make_unique<Scene>();
        scene->setBackColor({0.2f, 0.3f, 0.8f, 1.0f});

		auto sceneRenderer = std::unique_ptr<SceneRenderer>(new GenericSceneRenderer(this->graphicsDriver.get()));

		this->sceneManager = std::make_unique<SceneManager>(std::move(scene));
		this->sceneManager->setSceneRenderer(std::move(sceneRenderer));
		
		this->scene = this->sceneManager->getScene();

        this->camera = this->scene->createCamera();
		this->camera->setPosition({0.0f, 2.0f, 4.0f});
		this->camera->setLookAt({0.0f, 0.0f, 0.0f});

		this->camera->setViewport(Rectf((Size2f)this->graphicsDriver->getDisplayMode().size));
		
		Mesh *boxMesh = this->getMeshManager()->generateBoxMesh("boxMesh", this->graphicsDriver.get(), {0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f});

		this->scene->createSceneNode("boxSceneNode", boxMesh);

		this->animator = std::make_unique<SpatialAnimator>();
		this->animator->setSceneNode(this->scene->getRootNode()->getChild("boxSceneNode"));
		this->sceneManager->addAnimator(this->animator.get());
    }
    
    virtual ApplicationStatus::Enum getStatus() const override 
    {
        return this->status;
    }
    
    virtual void pollEvents() override
    {
        this->graphicsDriver->pollEvents();
    }
    
    virtual void update(double seconds) override 
    {
		this->sceneManager->update(seconds);
    }
    
    virtual void render() override 
    {
		this->sceneManager->render(this->camera);
    }
    
    virtual void handleEvent(const EventData &data) override 
    {
        const InputEventData &inputData = data.cast<InputEventData>();
        
        if (inputData.check(ButtonStatus::Press, ButtonCode::KeyEsc)) {
            this->status = ApplicationStatus::Terminated;
        }
    }

private:
    std::unique_ptr<GraphicsDriver> graphicsDriver;
	std::unique_ptr<Material> material;
	MaterialFormat materialFormat;

	std::unique_ptr<SceneManager> sceneManager;
	std::unique_ptr<SceneNodeAnimator> animator;
	
	Scene* scene = nullptr;
	Camera *camera = nullptr;
    ApplicationStatus::Enum status = ApplicationStatus::Running;
};

int main(int argc, char **argv) 
{
    return Application::execute<Demo01>(argc, argv);
}
