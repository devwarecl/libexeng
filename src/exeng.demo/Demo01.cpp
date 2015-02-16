
#include <boost/filesystem/path.hpp>
#include <exeng/framework/GraphicsApplication.hpp>
#include <exeng/system/PluginManager.hpp>

using namespace exeng;
using namespace exeng::framework;

class Demo01 : public GraphicsApplication {
public:
    virtual void initialize(int argc, char **argv) override 
    {
        this->getRoot()->getPluginManager()->loadPlugins();
    }
};

int main(int argc, char **argv) 
{
    return Application::execute<Demo01>(argc, argv);
}
