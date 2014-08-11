/**
 * @file RayTracer.hpp
 * @brief Interfaz de un trazador de rayos
 */

#ifndef __RAYTRACER_TRACERS_HARDWARETRACER_HPP__
#define __RAYTRACER_TRACERS_HARDWARETRACER_HPP__

#include <exeng/Exeng.hpp>
#include <memory>

#include "Tracer.hpp"
#include "../samplers/Sampler.hpp"

namespace raytracer { namespace tracers {
    class HardwareTracer : public Tracer {
    public:
        HardwareTracer(const exeng::scenegraph::Scene *scene, const raytracer::samplers::Sampler *sampler);
        virtual void render(const exeng::scenegraph::Camera *camera);
        ~HardwareTracer();
        
        virtual void setRenderTarget(exeng::graphics::Texture *renderTarget);
        
    private:
        struct Private;
        std::unique_ptr<Private> impl;
    };
}}

#endif // __RAYTRACER_TRACERS_TRACER_HPP__
