/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__
#define __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__

#include <exeng/framework/Application.hpp>
#include <exeng/Timer.hpp>

namespace exeng { namespace framework {
    
    /**
     * @brief Default application interface for graphics applications
     */
    class GraphicsApplication : public Application {
    public:
        GraphicsApplication();
        
        virtual ~GraphicsApplication() = 0;
        
        virtual int run(int argc, char **argv) override;
        
        
    protected:
        virtual int getExitCode() const;
        
        virtual ApplicationStatus::Enum getStatus() const;
        
        virtual void initialize(int argc, char **argv);
        
        virtual void terminate();
        
        virtual void pollEvents();
        
        virtual void update(double frameTime);
        
        virtual void render();
    };
    
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
            frameTimeMs = Timer::getTime() - lastTime;
            lastTime = Timer::getTime();
            
            this->pollEvents();
            this->update(frameTimeMs / 1000.0);
            this->render();
        }
        
        return this->getExitCode();
    }
    
    inline void GraphicsApplication::initialize(int argc, char **argv) {}
    inline void GraphicsApplication::terminate() {}
    inline void GraphicsApplication::pollEvents() {}
    inline void GraphicsApplication::update(double frameTime) {}
    inline void GraphicsApplication::render() {}
    
    inline ApplicationStatus::Enum GraphicsApplication::getStatus() const 
    {
        return ApplicationStatus::Terminated;
    }
    
    inline int GraphicsApplication::getExitCode() const 
    {
        return 0;
    }
}}

#endif // __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__
