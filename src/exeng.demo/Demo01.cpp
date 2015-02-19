
#include <boost/filesystem/path.hpp>
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

class Demo01 : public GraphicsApplication {
public:
    virtual void initialize(int argc, char **argv) override 
    {
        this->getRoot()->getPluginManager()->setPluginPath("../../plugins/libexeng.graphics.gl3/");
        this->getRoot()->getPluginManager()->loadPlugin("exeng.graphics.gl3");
        
		this->getRoot()->getSceneManager()->setScene(this->scene.get());

        this->graphicsDriver = this->getRoot()->getGraphicsManager()->createDriver();
        this->graphicsDriver->initialize();

		this->scene = std::unique_ptr<Scene>(new Scene());

		this->sceneRenderer = std::unique_ptr<SceneRenderer>(new GenericSceneRenderer(this->graphicsDriver.get()));
		this->sceneRenderer->setScene(this->scene.get());
    }
    
    virtual ApplicationStatus::Enum getStatus() const override 
    {
        return ApplicationStatus::Running;
    }
    
    virtual void update(double seconds) override 
    {
        
    }
    
    virtual void render() override 
    {
		this->sceneRenderer->renderScene(this->camera);
    }
    
private:
    std::unique_ptr<GraphicsDriver> graphicsDriver;
	std::unique_ptr<Scene> scene;
	std::unique_ptr<SceneRenderer> sceneRenderer;

	Camera *camera = nullptr;
};

int main(int argc, char **argv) 
{
    return Application::execute<Demo01>(argc, argv);
}
