
#include "Application.hpp"
#include <stdexcept>
#include <iostream>

namespace RayTracer {
    int Application::run(const StringVector& cmdLine) {
        try {
            Application *app = Application::instance;
            int exitCode = 0;
            double seconds = 0.0;
            
            app->initialize(cmdLine);
            
            while (app->getStatus() != ApplicationStatus::Stopped) {
                seconds = app->getFrameTime();
                
                app->processInput();
                app->update(seconds);
                app->present();
            }
            
            app->terminate();
            
            exitCode = app->getExitCode();
            
            // No olvidar limpiar el puntero
            delete app;
            Application::instance = nullptr;
            
            return exitCode;
        }
        catch(const std::exception &exp) {
            std::cout << "Unhandled exception " << exp.what() << std::endl;
            return -1;
        }
    }


    bool Application::set(Application *app)  {
        if (Application::instance != NULL) {
            delete Application::instance;
            Application::instance = nullptr;
        }
        
        Application::instance = app;
		
        return true;
    }


    Application *Application::instance = nullptr;
}


int main(int argc, char** argv) {
    using namespace RayTracer;

    RayTracer::StringVector cmdLine;

    // Inicializar la linea de comandos
    cmdLine.reserve(argc);
    cmdLine.resize(argc);

    for(int i=0; i<argc; ++i) {
        cmdLine[i] = std::string(argv[i]);
    }

    // Ejecutar la aplicacion
    return RayTracer::Application::run(cmdLine);
}
