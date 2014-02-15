
#ifndef __RAYTRACER_RAYTRACERAPP_HPP__
#define __RAYTRACER_RAYTRACERAPP_HPP__

#include <exeng/Exeng.hpp>
#include <exeng/scenegraph/SceneManager.hpp>
#include <vector>
#include <list>
#include <boost/scoped_ptr.hpp>

#include <exeng.raytracer/samplers/Sampler.hpp>
#include <exeng.raytracer/tracers/Tracer.hpp>

namespace raytracer {
    typedef std::list<exeng::scenegraph::SceneNode*> SceneNodeList;
    typedef SceneNodeList::iterator SceneNodeListIt;
    
    class RayTracerApp : public exeng::framework::Application, public exeng::input::IEventHandler {
    public:
        RayTracerApp();
        
        virtual ~RayTracerApp();
        
        virtual void initialize(const exeng::framework::StringVector& cmdLine);
    
        virtual double getFrameTime() const;
        
        virtual void pollEvents();
        
        virtual exeng::framework::ApplicationStatus::Enum getStatus() const;
        
        virtual void update(double seconds);
        
        virtual void render();
        
        virtual int getExitCode() const;
        
        virtual void terminate();
        
        virtual void handleEvent(const exeng::input::EventData &data);
        
    private:
        void clear();
        
        void present();
        
        void loadScene();
        
    private:
        //! El color por defecto a usar en caso de que ningun rayo colisione con la escena.
        // std::uint32_t defaultColor;
        
        boost::scoped_ptr<exeng::Root> root;
        boost::scoped_ptr<exeng::graphics::Material> material;
        boost::scoped_ptr<exeng::graphics::GraphicsDriver> driver;
        boost::scoped_ptr<exeng::graphics::VertexBuffer> vertexBuffer;
        boost::scoped_ptr<exeng::graphics::Texture> texture;
        boost::scoped_ptr<exeng::scenegraph::Scene> scene;
        boost::scoped_ptr<raytracer::samplers::Sampler> sampler;
        
        boost::scoped_ptr<exeng::graphics::Material> boxMaterial;
        
        exeng::framework::ApplicationStatus::Enum applicationStatus;
        
        mutable uint32_t lastTime;
        
        uint32_t fpsCurrent;
        double fpsLastTime;
        double fpsCurrentTime;
        
        boost::scoped_ptr<raytracer::tracers::Tracer> tracer;
        boost::scoped_ptr<exeng::scenegraph::Camera> camera;
        
        exeng::graphics::ButtonStatus::Enum buttonStatus[exeng::graphics::ButtonCode::Count];
    };

}

#endif	//__RAYTRACER_RAYTRACERAPP_HPP__
