
#ifndef __RAYTRACER_RAYTRACERAPP_HPP__
#define __RAYTRACER_RAYTRACERAPP_HPP__

#include <vector>
#include <list>
#include <memory>
#include <exeng/Exeng.hpp>
#include <exeng/Vector.hpp>
#include <exeng/framework/GraphicsApplication.hpp>
#include <exeng/graphics/Texture.hpp>
#include <exeng/scenegraph/SceneManager.hpp>
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
               const exeng::Vector3f& size, 
               const exeng::Vector4f &color
        );
        
        void clear();
        void present();
        void loadScene();
        
    private:
        exeng::graphics::Material material;
        exeng::scenegraph::Camera camera;
        std::unique_ptr<exeng::graphics::GraphicsDriver> driver;
        std::unique_ptr<exeng::graphics::VertexBuffer> vertexBuffer;
        std::unique_ptr<exeng::graphics::Texture> texture;
        std::unique_ptr<raytracer::samplers::Sampler> sampler;
        exeng::framework::ApplicationStatus::Enum applicationStatus;
        std::unique_ptr<raytracer::tracers::Tracer> tracer;
        std::unique_ptr<exeng::scenegraph::Scene> scene;

        mutable uint32_t lastTime;
        SceneLoader sceneLoader;
        FpsCounter frameCounter;

        exeng::graphics::ButtonStatus::Enum buttonStatus[exeng::graphics::ButtonCode::Count];
    };
}

#endif	//__RAYTRACER_RAYTRACERAPP_HPP__
