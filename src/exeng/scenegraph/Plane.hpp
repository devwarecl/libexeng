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


#ifndef __EXENG_SCENEGRAPH_PLANE_HPP__
#define __EXENG_SCENEGRAPH_PLANE_HPP__

#include <exeng/math/TVector.hpp>
#include <exeng/scenegraph/Ray.hpp>
#include <exeng/scenegraph/IntersectInfo.hpp>

namespace exeng { namespace scenegraph {
    
class Ray;

struct IntersectInfo;

/**
    * @brief Plano en el espacio tridimensional. 
    */
class Plane {
public:
    /**
        * @brief Construye un plano centrado en el origen, cuya direccion perpendicular es el eje +Y.
        */
    Plane();
    
    /**
        * @brief Plane
        * @param point
        * @param normal
        */
    Plane(const exeng::math::Vector3f& point, 
            const exeng::math::Vector3f& normal);
    
    /**
        * @brief Plane
        * @param p1
        * @param p2
        * @param p3
        */
    Plane(const exeng::math::Vector3f& p1, 
            const exeng::math::Vector3f& p2, 
            const exeng::math::Vector3f& p3);
    
    /**
        * @brief Inicializa un objeto de planos
        * @param basePoint
        * @param normal
        */
    void set(const exeng::math::Vector3f& point, 
                const exeng::math::Vector3f& normal);
    
    /**
        * @brief Inicializa un plano a partir de tres puntos en el espacio
        */
    void set(const exeng::math::Vector3f& p1, 
                const exeng::math::Vector3f& p2, 
                const exeng::math::Vector3f& p3);
    
    /**
        * @brief  Establece la direccion perpendicular al plano.
        * @param normal
        */
    void setNormal(const exeng::math::Vector3f& normal);
    
    /**
        * @brief Devuelve el vector perpendicular al plano.
        * @return 
        */
    exeng::math::Vector3f getNormal() const;
    
    /**
        * @brief Establece el punto base del plano. Este punto no posee restriccion alguna.
        * @param point
        */
    void setPoint(const exeng::math::Vector3f& point);
    
    /**
        * @brief Devuelve una copia del punto base del plano.
        * @return 
        */
    exeng::math::Vector3f getPoint() const;
    
    /**
        * @brief Calcula la interseccion entre un plano y un rayo.
        * @param ray El rayo con el cual calcular la interseccion
        * @param intersectInfo Puntero a IntersectInfo, que almacenara la informacion sobre la interseccion.
        * @return Valor booleano. 'true' si hubo interseccion entre el rayo y el 
        * plano, y 'falso' en caso contrario.
        * 
        */
    bool intersect(const Ray& ray, IntersectInfo* intersectInfo=nullptr) const;
    
private:
    exeng::math::Vector3f normal;   //! Plane normal vector
    exeng::math::Vector3f point;    //! Plane base point
};

}}


std::ostream& operator<< (std::ostream& os, const exeng::scenegraph::Plane &plane);


namespace exeng { namespace scenegraph {
    
inline Plane::Plane() {
    this->set( exeng::math::Vector3f(0.0), exeng::math::Vector3f(0.0f, 1.0f, 0.0f) );
}


inline Plane::Plane(const exeng::math::Vector3f& point, const exeng::math::Vector3f& normal) {
    this->set(point, normal);
}


inline Plane::Plane(const exeng::math::Vector3f& p1, const exeng::math::Vector3f& p2, const exeng::math::Vector3f& p3) {   
    this->set(p1, p2, p3);
}


inline void Plane::set(const exeng::math::Vector3f& point, const exeng::math::Vector3f& normal) {
    this->setPoint(point);
    this->setNormal(normal);
}


inline void Plane::set(const exeng::math::Vector3f& p1, 
                        const exeng::math::Vector3f& p2, 
                        const exeng::math::Vector3f& p3) {
    
    exeng::math::Vector3f v1 = p2 - p1;
    exeng::math::Vector3f v2 = p3 - p1;
    
    exeng::math::Vector3f normal = v1.cross(v2);
    exeng::math::Vector3f point = (1.0f/3.0f) * (p1 + p2 + p3);
    
    this->set(point, normal);
}


inline void Plane::setNormal(const exeng::math::Vector3f& normal) {
    this->normal = normal;
    this->normal.normalize();
}


inline void Plane::setPoint(const exeng::math::Vector3f& point) {
    this->point = point;
}


inline exeng::math::Vector3f Plane::getNormal() const {
    return this->normal;
}


inline exeng::math::Vector3f Plane::getPoint() const {
    return this->point;
}


inline bool Plane::intersect(const Ray& ray, IntersectInfo* intersectInfo) const {
    using namespace exeng::math;
    
    auto p = this->point;
    auto n = this->normal;
    
    auto r = ray.getPoint();
    auto d = ray.getDirection();
    
    auto t = n.dot(p - r) /  n.dot(d);
    
    bool result = false;
    
    if (t > 0.0f) {
        result = true;
    }
    
    if (intersectInfo != nullptr) {
        intersectInfo->intersect = result;
        intersectInfo->distance = t;
        intersectInfo->normal = this->normal;
        intersectInfo->point = ray.getPointAt(t);
    }
    
    return result;
}

}}


inline std::ostream& operator<< (std::ostream& os, const exeng::scenegraph::Plane &plane) {
    return os << "Point : {" << plane.getPoint() << "}, Normal : {" << plane.getNormal() << "}";
}


#endif	//__EXENG_SCENEGRAPH_PLANE_HPP__
