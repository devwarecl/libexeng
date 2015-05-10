
#include "GraphicsApplication.hpp"

namespace exeng { namespace framework {

	struct ApplicationGuard {
		ApplicationGuard (GraphicsApplication* app_, int argc, char **argv) {
			this->app = app_;
			this->app->initialize(argc, argv);
		}
            
		~ApplicationGuard () {
			this->app->terminate(); 
		}
            
		GraphicsApplication *app = nullptr;
	};

    int GraphicsApplication::run(int argc, char **argv) {
        uint32_t lastTime = Timer::getTime();
        uint32_t frameTime = 0;
        
        ApplicationGuard appGuard(this, argc, argv);
        
        while (this->getApplicationStatus() == ApplicationStatus::Running) {
            frameTime = Timer::getTime() - lastTime;
            lastTime = Timer::getTime();
            
            this->pollEvents();
            this->update(frameTime / 1000.0f);
            this->render();
        }
        
        return this->getExitCode();
    }
}}
