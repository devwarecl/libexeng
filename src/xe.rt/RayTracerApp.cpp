
#include "RayTracerApp.hpp"

#include <xe.main/Main.hpp>

namespace xe { namespace rt {
    RayTracerApp::RayTracerApp() {}
    
    RayTracerApp::~RayTracerApp() {
        this->terminate();
    }
    
    void RayTracerApp::initialize() {}
    
    void RayTracerApp::terminate() {}
    
    void RayTracerApp::doEvents() {}
    
    void RayTracerApp::update(const float seconds) {}
    
    void RayTracerApp::render() {}
    
    bool RayTracerApp::isRunning() const {
        return false;
    }
}}

namespace xe {
    int main(int argc, char **argv) {
        xe::rt::RayTracerApp app;
        return Application::execute(app, argc, argv);
    }
}
