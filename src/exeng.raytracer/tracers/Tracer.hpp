///**
// * @file Tracer.hpp
// * @brief Interfaz de un trazador de rayos
// */
//
//#ifndef __RAYTRACER_TRACERS_TRACER_HPP__
//#define __RAYTRACER_TRACERS_TRACER_HPP__
//
//#include <exeng/graphics/Texture.hpp>
//#include <exeng/scenegraph/Scene.hpp>
//#include <exeng/scenegraph/Camera.hpp>
//
//#include <exeng.raytracer/samplers/Sampler.hpp>
//
//namespace raytracer { namespace tracers {
//    class Tracer {
//    public:
//        Tracer(const exeng::scenegraph::Scene *scene, const raytracer::samplers::Sampler *sampler);
//        
//        virtual ~Tracer();
//        
//        virtual void setRenderTarget(exeng::graphics::Texture *renderTarget);
//        virtual exeng::graphics::Texture* getRenderTarget();
//        virtual const exeng::graphics::Texture* getRenderTarget() const;
//        
//        virtual const exeng::scenegraph::Scene* getScene();
//        virtual const raytracer::samplers::Sampler* getSampler();
//        
//        virtual const exeng::scenegraph::Scene* getScene() const;
//        virtual const raytracer::samplers::Sampler* getSampler() const;
//        
//        virtual void render(const exeng::scenegraph::Camera *camera) = 0;
//        
//    private:
//        exeng::graphics::Texture *renderTarget;
//        const exeng::scenegraph::Scene *scene;
//        const raytracer::samplers::Sampler* sampler;
//    };
//}}
//
//#endif  // __RAYTRACER_TRACERS_TRACER_HPP__
