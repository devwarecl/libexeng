
#include <raytracer/tracers/Tracer.hpp>

namespace raytracer { namespace tracers {
    using namespace exeng;
    using namespace exeng::graphics;
    using namespace exeng::scenegraph;
    
    using namespace raytracer::samplers;
    
    Tracer::Tracer(Texture *renderTarget, const Scene *scene, const Sampler *sampler) 
        : renderTarget(nullptr), scene(nullptr), sampler(nullptr)  {
        assert(renderTarget != nullptr);
        assert(scene != nullptr);
        
        this->renderTarget = renderTarget;
        this->scene = scene;
        this->sampler = sampler;
    }
    
    
    Tracer::~Tracer() {
    }
}}
