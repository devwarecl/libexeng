
#include <boost/filesystem/path.hpp>
#include <exeng/input/IEventHandler.hpp>
#include <exeng/framework/GraphicsApplication.hpp>
#include <exeng/system/PluginManager.hpp>
#include <exeng/graphics/GraphicsManager.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/scenegraph/Scene.hpp>
#include <exeng/scenegraph/SceneManager.hpp>
#include <exeng/scenegraph/GenericSceneRenderer.hpp>

using namespace exeng;
using namespace exeng::framework;
using namespace exeng::graphics;
using namespace exeng::scenegraph;
using namespace exeng::input;

class Demo01 : public GraphicsApplication, public IEventHandler {
public:
    virtual void initialize(int argc, char **argv) override 
    {
        this->getRoot()->getPluginManager()->setPluginPath("../../plugins/libexeng.graphics.gl3/");
        this->getRoot()->getPluginManager()->loadPlugin("exeng.graphics.gl3");
        
		this->getRoot()->getSceneManager()->setScene(this->scene.get());
        
        this->graphicsDriver = this->getRoot()->getGraphicsManager()->createDriver();
        this->graphicsDriver->addEventHandler(this);
        this->graphicsDriver->initialize();
        
		this->scene = std::unique_ptr<Scene>(new Scene());
        this->scene->setBackColor({0.2f, 0.3f, 0.8f, 1.0f});

        this->camera = this->scene->createCamera();
        
		this->sceneRenderer = std::unique_ptr<SceneRenderer>(new GenericSceneRenderer(this->graphicsDriver.get()));
		this->sceneRenderer->setScene(this->scene.get());
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
