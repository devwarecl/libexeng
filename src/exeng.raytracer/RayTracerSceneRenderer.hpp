
#ifndef __RAYTRACER_RAYTRACERSCENERENDERER_HPP__
#define __RAYTRACER_RAYTRACERSCENERENDERER_HPP__

#include <exeng/scenegraph/Camera.hpp>
#include <exeng/scenegraph/Scene.hpp>
#include <exeng/scenegraph/ISceneRenderer.hpp>

#include <exeng.raytracer/tracers/Tracer.hpp>

namespace raytracer {
    /**
     * @brief Renderizador de escenas, implementado como un trazador de rayos
     */
    class RayTracerSceneRenderer : public exeng::scenegraph::ISceneRenderer {
    public:
        RayTracerSceneRenderer();
        RayTracerSceneRenderer(raytracer::tracers::Tracer *tracer);
        
        virtual ~RayTracerSceneRenderer();
        
        virtual void renderScene(const exeng::scenegraph::Scene *scene, const exeng::scenegraph::Camera *camera);
        
        void setTracer(raytracer::tracers::Tracer *tracer);
        const raytracer::tracers::Tracer* getTracer() const;
        raytracer::tracers::Tracer* getTracer();
        
    private:
        raytracer::tracers::Tracer* tracer;
    };

}
#endif // __RAYTRACER_RAYTRACERSCENERENDERER_HPP__

