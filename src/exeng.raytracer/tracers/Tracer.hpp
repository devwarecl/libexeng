/**
 * @file Tracer.hpp
 * @brief Interfaz de un trazador de rayos
 */

#ifndef __RAYTRACER_TRACERS_TRACER_HPP__
#define __RAYTRACER_TRACERS_TRACER_HPP__

#include <exeng/graphics/Texture.hpp>
#include <exeng/scenegraph/Scene.hpp>
#include <exeng/scenegraph/Camera.hpp>

#include <exeng.raytracer/samplers/Sampler.hpp>

namespace raytracer { namespace tracers {
    class Tracer {
    public:
        Tracer(exeng::graphics::Texture *renderTarget, const exeng::scenegraph::Scene *scene, const raytracer::samplers::Sampler *sampler);
        
        virtual ~Tracer();
        virtual void render(const exeng::scenegraph::Camera *camera) = 0;
        
        const exeng::scenegraph::Scene *getScene() const;
        const exeng::scenegraph::Camera *getcamera;
        const raytracer::samplers::Sampler *sampler;
        
    protected:
        exeng::graphics::Texture *renderTarget;
        const exeng::scenegraph::Scene *scene;
        const exeng::scenegraph::Camera *camera;
    };
}}

#endif  // __RAYTRACER_TRACERS_TRACER_HPP__
