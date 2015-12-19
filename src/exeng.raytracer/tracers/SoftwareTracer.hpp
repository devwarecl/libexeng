//
//#ifndef __RAYTRACER_TRACERS_SOFTWARETRACER_HPP__
//#define __RAYTRACER_TRACERS_SOFTWARETRACER_HPP__
//
//#include <exeng.raytracer/tracers/Tracer.hpp>
//
//#include <exeng.raytracer/samplers/Sampler.hpp>
//#include <list>
//#include <exeng/scenegraph/Ray.hpp>
//#include <exeng/scenegraph/IntersectInfo.hpp>
//#include <exeng/scenegraph/Camera.hpp>
//#include <exeng/scenegraph/SceneNode.hpp>
//
//namespace raytracer { namespace tracers {
//    class SoftwareTracer : public Tracer {
//    public:
//        SoftwareTracer(const xe::sg::Scene *scene, const raytracer::samplers::Sampler *sampler);
//        virtual ~SoftwareTracer();
//        virtual void render(const xe::sg::Camera *camera);
//        
//    private:
//        uint32_t getOffset(const xe::Vector2i &point) const;
//        
//        void putPixel(std::uint32_t *backbuffer, const xe::Vector2i &point, const std::uint32_t color);
//        
//        std::uint32_t getPixel(std::uint32_t *backbuffer, const xe::Vector2i &point) const;
//        
//        xe::sg::Ray castRay(const xe::Vector2f &pixel, const xe::sg::Camera *camera) const;
//        xe::sg::Ray castRay(const xe::Vector2f &pixel, const xe::sg::Camera *camera, const xe::Vector2f &sample) const;
//        xe::sg::IntersectInfo intersectRay(const std::list<const xe::sg::SceneNode*> &nodes, const xe::sg::Ray &ray) const;
//
//        xe::Vector4f traceRay(const std::list<const xe::sg::SceneNode*> &nodeList, const xe::Vector2i &pixel, const xe::sg::Camera *camera) const;
//        xe::Vector4f traceRayMultisampled(const std::list<const xe::sg::SceneNode*> &nodeList, const xe::Vector2i &pixel, const xe::sg::Camera *camera) const;
//        
//        void flattenHierarchy(std::list<const xe::sg::SceneNode*> &out, const xe::sg::SceneNode* node) const;
//    };
//}}
//
//#endif  //__RAYTRACER_TRACERS_SOFTWARETRACER_HPP__
