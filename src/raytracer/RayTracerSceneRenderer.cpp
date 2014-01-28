
#include <raytracer/RayTracerSceneRenderer.hpp>

namespace raytracer {

    using namespace raytracer;
    using namespace raytracer::tracers;
    
    using namespace exeng;
    using namespace exeng::scenegraph;
    
    RayTracerSceneRenderer::RayTracerSceneRenderer() : tracer(nullptr) {}
    RayTracerSceneRenderer::RayTracerSceneRenderer(Tracer *tracer_) : tracer(tracer_) {}
    RayTracerSceneRenderer::~RayTracerSceneRenderer() {}
    
    void RayTracerSceneRenderer::renderScene(const Scene *scene, const Camera *camera) {
        if (this->getTracer()==nullptr) {
            throw std::runtime_error("RayTracerSceneRenderer::renderScene: Debe existir un Trazador no nulo.");
        }
        
        this->getTracer()->render(camera);
    }
    
    void RayTracerSceneRenderer::setTracer(Tracer *tracer) {
        this->tracer = tracer;
    }
    
    const Tracer* RayTracerSceneRenderer::getTracer() const {
        return this->getTracer();
    }
    
    
    Tracer* RayTracerSceneRenderer::getTracer() {
        return this->tracer;    
    }

}
