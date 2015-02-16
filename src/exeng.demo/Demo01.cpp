
#include <boost/filesystem/path.hpp>
#include <exeng/framework/GraphicsApplication.hpp>
#include <exeng/system/PluginManager.hpp>
#include <exeng/graphics/GraphicsManager.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>

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
        
        this->graphicsDriver = std::move(this->getRoot()->getGraphicsManager()->createDriver());
        this->graphicsDriver->initialize();
    }
    
    virtual ApplicationStatus::Enum getStatus() const override 
    {
        return ApplicationStatus::Running;
    }
    
    virtual void pollEvents() override 
    {
        
    }
    
    virtual void update(double seconds) override 
    {
        
    }
    
    virtual void render() override 
    {
        this->graphicsDriver->beginFrame({0.0f, 0.2f, 0.8f, 1.0f}, ClearFlags::Color);
        
        this->graphicsDriver->endFrame();
    }
    
private:
    std::unique_ptr<GraphicsDriver> graphicsDriver;
};

int main(int argc, char **argv) 
{
    return Application::execute<Demo01>(argc, argv);
}
