//
//#ifndef __RAYTRACER_RAYTRACERSCENERENDERER_HPP__
//#define __RAYTRACER_RAYTRACERSCENERENDERER_HPP__
//
//#include <xe/sg/Camera.hpp>
//#include <xe/sg/Scene.hpp>
//#include <xe/sg/SceneRenderer.hpp>
//
//#include <exeng.raytracer/tracers/Tracer.hpp>
//
//namespace raytracer {
//    /**
//     * @brief Ray tracer scene renderer
//     */
//    class RayTracerSceneRenderer : public xe::sg::SceneRenderer {
//    public:
//        RayTracerSceneRenderer(const xe::sg::Scene *scene, raytracer::tracers::Tracer *tracer);
//        
//        virtual ~RayTracerSceneRenderer();
//        virtual void renderScene(const xe::sg::Camera *camera);
//
//    private:
//		xe::sg::Scene* scene = nullptr;
//        raytracer::tracers::Tracer* tracer = nullptr;
//    };
//}
//#endif // __RAYTRACER_RAYTRACERSCENERENDERER_HPP__
