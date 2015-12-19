//
//#include <exeng.raytracer/tracers/Tracer.hpp>
//
//namespace raytracer { namespace tracers {
//    using namespace xe;
//    using namespace xe::gfx;
//    using namespace xe::sg;
//    
//    using namespace raytracer::samplers;
//    
//    Tracer::Tracer(const Scene *scene, const Sampler *sampler) : renderTarget(nullptr), scene(nullptr), sampler(nullptr) {
//        this->scene = scene;
//        this->sampler = sampler;
//    }
//    
//    void Tracer::setRenderTarget(Texture *renderTarget) {
//        this->renderTarget = renderTarget;
//    }
//    
//    Texture* Tracer::getRenderTarget() {
//        return this->renderTarget;
//    }
//    
//    const Texture* Tracer::getRenderTarget() const {
//        return this->renderTarget;
//    }
//    
//    const Scene* Tracer::getScene() {
//        return this->scene;
//    }
//    
//    const Sampler* Tracer::getSampler() {
//        return this->sampler;
//    }
//    
//    const Scene* Tracer::getScene() const {
//        return this->scene;
//    }
//    
//    const Sampler* Tracer::getSampler() const {
//        return this->sampler;
//    }
//    
//    Tracer::~Tracer() {}
//}}
