
#include "Application.hpp"
#include <stdexcept>
#include <iostream>

#include <exeng/DataType.hpp>
#include <memory>

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
        }
        catch(const std::exception &exp) {
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
