
#include <exeng/Exeng.hpp>
#include <exeng/framework/GraphicsApplication.hpp>

using namespace exeng;
using namespace exeng::framework;
using namespace exeng::graphics;
using namespace exeng::scenegraph;
using namespace exeng::input;

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

		this->getPluginManager()->setPluginPath(pluginPath);
        this->getPluginManager()->loadPlugin("exeng.graphics.gl3");
		
        this->graphicsDriver = this->getRoot()->getGraphicsManager()->createDriver();
        this->graphicsDriver->addEventHandler(this);
        this->graphicsDriver->initialize();
        
		this->scene = std::unique_ptr<Scene>(new Scene());
        this->scene->setBackColor({0.2f, 0.3f, 0.8f, 1.0f});

        this->camera = this->scene->createCamera();
		this->camera->setPosition({0.0f, 2.0f, 4.0f});
		this->camera->setLookAt({0.0f, 0.0f, 0.0f});

		this->camera->setViewport(Rectf((Size2f)this->graphicsDriver->getDisplayMode().size));
		
		this->sceneRenderer = std::unique_ptr<SceneRenderer>(new GenericSceneRenderer(this->graphicsDriver.get()));
		this->sceneRenderer->setScene(this->scene.get());

		Mesh *boxMesh = this->getMeshManager()->generateBoxMesh("boxMesh", this->graphicsDriver.get(), {0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f});

		this->scene->createSceneNode("boxSceneNode", boxMesh);
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
        
    }
    
    virtual void render() override 
    {
		this->sceneRenderer->renderScene(this->camera);
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
	std::unique_ptr<Scene> scene;
	std::unique_ptr<SceneRenderer> sceneRenderer;
    
	Camera *camera = nullptr;
    ApplicationStatus::Enum status = ApplicationStatus::Running;
};

int main(int argc, char **argv) 
{
    return Application::execute<Demo01>(argc, argv);
}
