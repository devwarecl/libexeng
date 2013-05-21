
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <cstdint>
#include <list>

#include "RayTracerAppPrivate.hpp"
#include <boost/timer/timer.hpp>

namespace raytracer {

    RayTracerApp::RayTracerApp() {
		this->impl.reset(new RayTracerApp::Private());
    }


    RayTracerApp::~RayTracerApp() {
        this->terminate();
    }


    void RayTracerApp::initialize(const StringVector& cmdLine) {
        SDL_Init(SDL_INIT_VIDEO);
        
        auto screenSize = this->impl->cameraView.size;
        
        auto flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
        auto buffer = SDL_SetVideoMode(screenSize.x, screenSize.y, 32, flags);

        this->impl->backbuffer = buffer;
        this->impl->running = true;
        
        this->impl->loadScene();
    }


    double RayTracerApp::getFrameTime() const {
        return 0.0;
    }


    void RayTracerApp::pollEvents() {
        while (SDL_PollEvent(&this->impl->event)) {
            switch (this->impl->event.type) {
                case SDL_QUIT:
                    this->impl->running = false;
                    break;
            }
        }
    }


    ApplicationStatus::Enum RayTracerApp::getStatus() {
        if (this->impl->running == true) {
            return ApplicationStatus::Running;
		} else {
            return ApplicationStatus::Stopped;
		}
    }


    void RayTracerApp::update(double seconds) {
    }


    void RayTracerApp::render() {
        boost::timer::auto_cpu_timer autoTimer;
        
        auto screenSize = this->impl->cameraView.size;
        IntersectInfo info;
        SceneNodeList nodeList;
        Vector2i pixel;
        Color pixelColor;
        
        this->impl->clear();
		this->impl->flattenHierarchy(nodeList, this->impl->scene->getRootNodePtr());
        
        for(pixel.y=0; pixel.y<screenSize.y; ++pixel.y) {
            for(pixel.x=0; pixel.x<screenSize.x; ++pixel.x) {
                
                pixelColor = this->impl->traceRay(nodeList, pixel);
                
                // Pintar el backbuffer 
				std::swap(pixelColor[0], pixelColor[1]);
                this->impl->putPixel(pixel, static_cast<uint32_t>(pixelColor));
            }
        }

        this->impl->present();
    }


    int RayTracerApp::getExitCode() const {
        return 0;
    }


    void RayTracerApp::terminate() {
        SDL_Quit();
    }
}


// Registrar la aplicacion de trazado de rayos
namespace {
    using namespace raytracer;
    static const bool b = Application::set( new RayTracerApp() );
}
