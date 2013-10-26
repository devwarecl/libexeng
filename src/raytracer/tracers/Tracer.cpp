

#include "Tracer.hpp"

namespace raytracer { namespace tracers {
    
using namespace exeng;
using namespace exeng::graphics;
using namespace exeng::scenegraph;

Tracer::Tracer(Texture *renderTarget, const Scene *scene) : renderTarget(nullptr), scene(nullptr)  {
    assert(renderTarget != nullptr);
    assert(scene != nullptr);
    
    this->renderTarget = renderTarget;
    this->scene = scene;
}

Tracer::~Tracer() {
}
    
}}
