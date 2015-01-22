/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include <exeng/scenegraph/Ray.hpp>
#include <exeng/scenegraph/IntersectInfo.hpp>

namespace exeng { namespace scenegraph {
    
inline Sphere::Sphere() {
    this->setAttributes(1.0f, exeng::Vector3f(0.0));
}


inline Sphere::Sphere(float radius) {
    this->setAttributes(radius, exeng::Vector3f(0.0));
}


inline Sphere::Sphere(float radius, const exeng::Vector3f &center) {
    this->setAttributes(radius, center);
}


inline void Sphere::setAttributes(float radius, const exeng::Vector3f &center){
    this->setRadius(radius);
    this->setCenter(center);
}


inline auto Sphere::setRadius(float radius) -> void {
    if (radius < 0.0f) {
        radius = 0.0;
    }
    
    this->radius = radius;
}


inline void Sphere::setCenter(const exeng::Vector3f &center) {
    this->center = center;
}


inline float Sphere::getRadius() const {
    return this->radius;
}


inline exeng::Vector3f Sphere::getCenter() const{
    return this->center;
}


inline bool Sphere::intersect(const Ray& ray, IntersectInfo *intersectInfo) const {
    
    // Variables de apoyo al algoritmo
    float t;
    bool result = false;

    // Variables del modelo matematico
    auto r0 = ray.getPoint();
    auto d = ray.getDirection();

    auto c = this->getCenter();
    auto r = this->getRadius();

    // Temporales para ahorrar calculos
    auto r_2 = r*r;

    auto r0_sub_c = r0 - c;
    auto r0_c_2 = abs2(r0_sub_c);

    // Temporales de la ecuacion cuadratica
    auto B = 2.0f * dot(d, r0_sub_c);
    auto C = r0_c_2 - r_2;

    // Calcular el discriminante
    auto disc = B*B - 4.0f*C;
    
    if (disc == 0.0f) {
        // Solo existe un punto de interseccion (el rayo es tangente a la esfera)
        t = -B / 2.0f;
        
        // Ver si el punto esta "adelante" del rayo, y no detras
        if (t > 0.0f) {
            result = true;
        }
    } else if (disc > 0.0f) {
        // Existen dos puntos de interseccion 
        auto rootDisc = std::sqrt(disc);

        // Determinar el primer punto de interseccion
        float t1 = ( -B - rootDisc ) / 2.0f;
        float t2 = ( -B + rootDisc ) / 2.0f;
        
        t = std::min(t1, t2);

        if (t > 0.0f) {
            result = true;
        }
    } else {
        // El rayo no toca a la esfera, ni por delante no por detras (caso mas comun)
        result = false;
    }
    
    // Rellenar la estructura con la informacion sobre las colisiones
    if (intersectInfo != nullptr) {
        intersectInfo->intersect = result;

        if (intersectInfo->intersect == true) {
            intersectInfo->normal = normalize(ray.getPointAt(t));
            intersectInfo->distance = t;
        }
    }
    
    return result;
}


inline bool Sphere::operator== (const Sphere &sphere) const {
    if (this->getCenter() != sphere.getCenter()) {
        return false;
    }
    
    if (this->getRadius() != sphere.getRadius()) {
        return false;
    }
    
    return true;
}


inline bool Sphere::operator!= (const Sphere &sphere) const {
    return ! (*this == sphere);
}  

}}
