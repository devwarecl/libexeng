
#include <exeng/Timer.hpp>

namespace exeng { namespace framework {
    
    inline GraphicsApplication::GraphicsApplication() {}
        
    inline GraphicsApplication::~GraphicsApplication() {}
    
    inline int GraphicsApplication::run(int argc, char **argv) {
        struct ApplicationGuard {
            ApplicationGuard (GraphicsApplication* app_, int argc, char **argv) : app(app_) {
                this->app->initialize(argc, argv);
            }
            
            ~ApplicationGuard (){ this->app->terminate(); }
            
            GraphicsApplication *app;
        };
        
        uint32_t lastTime = Timer::getTime();
        uint32_t frameTimeMs = 0;
        
        ApplicationGuard appGuard(this, argc, argv);
        
        while (this->getStatus() == ApplicationStatus::Running) {
            frameTimeMs = static_cast<double>(Timer::getTime() - lastTime) / 1000.0;
            lastTime = Timer::getTime();
            
            this->pollEvents();
            this->update(frameTimeMs);
            this->render();
        }
        
        return this->getExitCode();
    }
    
    inline void GraphicsApplication::initialize(int argc, char **argv) {}
     
    inline void GraphicsApplication::terminate() {}
        
    inline void GraphicsApplication::pollEvents() {}
        
    inline void GraphicsApplication::update(double frameTime) {}

    inline void GraphicsApplication::render() {}
    
    
    inline ApplicationStatus::Enum GraphicsApplication::getStatus() const {
        return ApplicationStatus::Terminated;
    }
    
    
    inline int GraphicsApplication::getExitCode() const {
        return 0;
    }
}}
