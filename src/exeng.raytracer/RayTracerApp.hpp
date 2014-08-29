
#ifndef __RAYTRACER_RAYTRACERAPP_HPP__
#define __RAYTRACER_RAYTRACERAPP_HPP__

#include <exeng/Exeng.hpp>
#include <exeng/framework/GraphicsApplication.hpp>
#include <exeng/graphics/Texture.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/scenegraph/SceneManager.hpp>
#include <vector>
#include <list>
#include <boost/scoped_ptr.hpp>

#include <exeng.raytracer/SceneLoader.hpp>
#include <exeng.raytracer/FpsCounter.hpp>
#include <exeng.raytracer/samplers/Sampler.hpp>
#include <exeng.raytracer/tracers/Tracer.hpp>

namespace raytracer {
    typedef std::list<exeng::scenegraph::SceneNode*> SceneNodeList;
    typedef SceneNodeList::iterator SceneNodeListIt;
    
    class RayTracerApp : public exeng::framework::GraphicsApplication, public exeng::input::IEventHandler {
    public:
        RayTracerApp();
        virtual ~RayTracerApp();
        
        /* exeng::framework::GraphicsApplication */
        virtual void initialize(int argc, char **argv);
        virtual void pollEvents();
        virtual exeng::framework::ApplicationStatus::Enum getStatus() const;
        virtual void update(double seconds);        
        virtual void render();
        virtual int getExitCode() const;
        virtual void terminate();
        
        /* exeng::input::IEventHandler*/
        virtual void handleEvent(const exeng::input::EventData &data);
        
    private:
        exeng::graphics::Texture* createTexture (
               exeng::graphics::GraphicsDriver *driver, 
               const exeng::math::Vector3f& size, 
               const exeng::math::Vector4f &color
        );
        
        void clear();
        void present();
        void loadScene();
        
    private:
        exeng::graphics::Material material;
        exeng::scenegraph::Camera camera;

        boost::scoped_ptr<exeng::graphics::GraphicsDriver> driver;
        boost::scoped_ptr<exeng::graphics::VertexBuffer> vertexBuffer;
        boost::scoped_ptr<exeng::graphics::Texture> texture;
        boost::scoped_ptr<raytracer::samplers::Sampler> sampler;
        
        exeng::framework::ApplicationStatus::Enum applicationStatus;
        
        mutable uint32_t lastTime;
        
        FpsCounter frameCounter;
        
        boost::scoped_ptr<raytracer::tracers::Tracer> tracer;
        
        SceneLoader sceneLoader;

        std::unique_ptr<exeng::scenegraph::Scene> scene;

        exeng::graphics::ButtonStatus::Enum buttonStatus[exeng::graphics::ButtonCode::Count];
    };
}

#endif	//__RAYTRACER_RAYTRACERAPP_HPP__
