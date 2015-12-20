///**
// * @file Tracer.hpp
// * @brief Interfaz de un trazador de rayos
// */
//
//#ifndef __RAYTRACER_TRACERS_TRACER_HPP__
//#define __RAYTRACER_TRACERS_TRACER_HPP__
//
//#include <xe/gfx/Texture.hpp>
//#include <xe/sg/Scene.hpp>
//#include <xe/sg/Camera.hpp>
//
//#include <exeng.raytracer/samplers/Sampler.hpp>
//
//namespace raytracer { namespace tracers {
//    class Tracer {
//    public:
//        Tracer(const xe::sg::Scene *scene, const raytracer::samplers::Sampler *sampler);
//        
//        virtual ~Tracer();
//        
//        virtual void setRenderTarget(xe::gfx::Texture *renderTarget);
//        virtual xe::gfx::Texture* getRenderTarget();
//        virtual const xe::gfx::Texture* getRenderTarget() const;
//        
//        virtual const xe::sg::Scene* getScene();
//        virtual const raytracer::samplers::Sampler* getSampler();
//        
//        virtual const xe::sg::Scene* getScene() const;
//        virtual const raytracer::samplers::Sampler* getSampler() const;
//        
//        virtual void render(const xe::sg::Camera *camera) = 0;
//        
//    private:
//        xe::gfx::Texture *renderTarget;
//        const xe::sg::Scene *scene;
//        const raytracer::samplers::Sampler* sampler;
//    };
//}}
//
//#endif  // __RAYTRACER_TRACERS_TRACER_HPP__
