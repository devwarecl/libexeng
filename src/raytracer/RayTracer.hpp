/**
 * @file RayTracer.hpp
 * @brief Interfaz del objeto trazador de rayos
 */

#ifndef __RAYTRACER_RAYTRACER_HPP__
#define __RAYTRACER_RAYTRACER_HPP__

#include <exeng/Exeng.hpp>
#include <memory>

namespace raytracer {
class RayTracer {
public:
    RayTracer( exeng::graphics::Texture &renderTarget, const exeng::scenegraph::Scene &scene );
    
    void render();
    
    ~RayTracer();    
    
private:
    struct Private;
    std::unique_ptr<Private> impl;
};
}

#endif // __RAYTRACER_RAYTRACER_HPP__
