#include "Application.hpp"
#include <stdexcept>
#include <iostream>

#include <exeng/Exeng.hpp>
#include <memory>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>

namespace raytracer {
    int Application::run(const StringVector& cmdLine) {
        
        std::unique_ptr<Application> app;
        
        try {
            app.reset(Application::instance);
            int exitCode = 0;
            double seconds = 0.0;
            
            app->initialize(cmdLine);
            
            while (app->getStatus() != ApplicationStatus::Stopped) {
                seconds = app->getFrameTime();
                
                app->pollEvents();
                app->update(seconds);
                app->render();
            }
            
            app->terminate();
            
            exitCode = app->getExitCode();

            return exitCode;
        } catch(const std::exception &exp) {
            std::cout << "Unhandled exception " << exp.what() << std::endl;
            return -1;
        }
    }


    bool Application::set(Application *app)  {
        if (Application::instance != nullptr) {
            delete Application::instance;
            Application::instance = nullptr;
        }
        
        Application::instance = app;
		
        return true;
    }
    
    Application *Application::instance = nullptr;
}


/*
int main(int argc, char** argv) {
    using namespace raytracer;

    raytracer::StringVector cmdLine;

    // Inicializar la linea de comandos
    cmdLine.reserve(argc);
    cmdLine.resize(argc);

    for(int i=0; i<argc; ++i) {
        cmdLine[i] = std::string(argv[i]);
    }
    
    // Ejecutar la aplicacion
    return raytracer::Application::run(cmdLine);
}
*/

using namespace exeng;
using namespace exeng::math;
using namespace exeng::graphics;


int main(int argc, char** argv) {
    
    // Load the opengl 3 driver
    auto root = boost::make_shared<Root>();
    root->getPluginManager()->load("exeng-graphics-gl3", "../exeng-graphics-gl3/");
    
    GraphicsDriver *driver = root->getGraphicsManager()->createDriver();
    
    DisplayMode mode = DisplayMode(Size2i(640, 480), 8, 8, 8, 8);
    mode.status = DisplayStatus::Window;
    mode.depthBits = 16;
    
    driver->initialize(mode);
    
    VertexFormat format;
    format.fields.push_back( VertexField(VertexAttrib::Position, 3, DataType::Float32) );
    VertexBuffer *buffer = driver->createVertexBuffer(format, 3);    
    {
        VertexArray<Vector3f> array( buffer );
        
        array[0] = Vector3f(0.0f, 1.0f, 0.0f);
        array[1] = Vector3f(1.0f, 0.0f, 0.0f);
        array[2] = Vector3f(-1.0f, 0.0f, 0.0f);
    }
    
    while(driver->isInitialized() == true) {
        driver->beginFrame(Color(0.2f, 0.2f, 0.8f, 1.0f), ClearFlags::Color);
        
        driver->setVertexBuffer(buffer);
        driver->render(Primitive::TriangleStrip, 3);
        
        driver->endFrame();
    }
    
    driver->terminate();
    delete driver;
    
    return 0;
}
