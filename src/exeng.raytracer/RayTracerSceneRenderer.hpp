//
//#ifndef __RAYTRACER_RAYTRACERSCENERENDERER_HPP__
//#define __RAYTRACER_RAYTRACERSCENERENDERER_HPP__
//
//#include <exeng/scenegraph/Camera.hpp>
//#include <exeng/scenegraph/Scene.hpp>
//#include <exeng/scenegraph/SceneRenderer.hpp>
//
//#include <exeng.raytracer/tracers/Tracer.hpp>
//
//namespace raytracer {
//    /**
//     * @brief Ray tracer scene renderer
//     */
//    class RayTracerSceneRenderer : public exeng::scenegraph::SceneRenderer {
//    public:
//        RayTracerSceneRenderer(const exeng::scenegraph::Scene *scene, raytracer::tracers::Tracer *tracer);
//        
//        virtual ~RayTracerSceneRenderer();
//        virtual void renderScene(const exeng::scenegraph::Camera *camera);
//
//    private:
//		exeng::scenegraph::Scene* scene = nullptr;
//        raytracer::tracers::Tracer* tracer = nullptr;
//    };
//}
//#endif // __RAYTRACER_RAYTRACERSCENERENDERER_HPP__
