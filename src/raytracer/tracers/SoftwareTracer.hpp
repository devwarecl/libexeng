
#ifndef __RAYTRACER_TRACERS_SOFTWARETRACER_HPP__
#define __RAYTRACER_TRACERS_SOFTWARETRACER_HPP__

#include <raytracer/tracers/Tracer.hpp>

#include <raytracer/samplers/Sampler.hpp>
#include <list>
#include <exeng/scenegraph/Ray.hpp>
#include <exeng/scenegraph/IntersectInfo.hpp>
#include <exeng/scenegraph/Camera.hpp>
#include <exeng/scenegraph/SceneNode.hpp>

namespace raytracer { namespace tracers {
    class SoftwareTracer : public Tracer {
    public:
        SoftwareTracer(exeng::graphics::Texture *renderTarget, const exeng::scenegraph::Scene *scene, const raytracer::samplers::Sampler *sampler);
        virtual ~SoftwareTracer();
        virtual void render(const exeng::scenegraph::Camera *camera);
        
    private:
        uint32_t 
        getOffset(const exeng::math::Vector2i &point) const;
        
        void 
        putPixel(std::uint32_t *backbuffer, const exeng::math::Vector2i &point, const std::uint32_t color);
        
        std::uint32_t 
        getPixel(std::uint32_t *backbuffer, const exeng::math::Vector2i &point) const;
        
        exeng::scenegraph::Ray 
        castRay(const exeng::math::Vector2f &pixel, const exeng::scenegraph::Camera *camera) const;
        
        exeng::scenegraph::Ray 
        castRay(const exeng::math::Vector2f &pixel, const exeng::scenegraph::Camera *camera, const exeng::math::Vector2f &sample) const;
        
        exeng::scenegraph::IntersectInfo 
        intersectRay(const std::list<const exeng::scenegraph::SceneNode*> &nodes, const exeng::scenegraph::Ray &ray) const;
        
        exeng::graphics::Color 
        traceRay(const std::list<const exeng::scenegraph::SceneNode*> &nodeList, const exeng::math::Vector2i &pixel, const exeng::scenegraph::Camera *camera) const;
        
        exeng::graphics::Color 
        traceRayMultisampled(const std::list<const exeng::scenegraph::SceneNode*> &nodeList, const exeng::math::Vector2i &pixel, const exeng::scenegraph::Camera *camera) const;
        
        void 
        flattenHierarchy(std::list<const exeng::scenegraph::SceneNode*> &out, const exeng::scenegraph::SceneNode* node) const;
    };
}}

#endif  //__RAYTRACER_TRACERS_SOFTWARETRACER_HPP__
