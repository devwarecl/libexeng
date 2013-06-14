
#ifndef __RAYTRACER_RAYTRACERAPP_HPP__
#define __RAYTRACER_RAYTRACERAPP_HPP__

#include <vector>
#include <boost/scoped_ptr.hpp>
#include <exeng/framework/Application.hpp>

namespace raytracer {
    
    class RayTracerApp : public exeng::framework::Application {
    public:
        RayTracerApp();
        
        virtual ~RayTracerApp();
        
        virtual void initialize(const exeng::framework::StringVector& cmdLine);

        virtual double getFrameTime() const;
        
        virtual void pollEvents();
        
        virtual exeng::framework::ApplicationStatus getStatus() const;
        
        virtual void update(double seconds);
        
        virtual void render();
        
        virtual int getExitCode() const;
        
        virtual void terminate();
        
    private:
        struct Private;
        boost::scoped_ptr<Private> impl;
    };
}

#endif	//__RAYTRACER_RAYTRACERAPP_HPP__

