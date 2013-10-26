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

#ifndef __EXENG_SCENEGRAPH_RAY_HPP__
#define __EXENG_SCENEGRAPH_RAY_HPP__

#include <iosfwd>

#include <exeng/Config.hpp>
#include <exeng/math/TVector.hpp>

namespace exeng { namespace scenegraph { 
    
/**
 * @brief Abstraccion de un rayo.
 *
 * Encapsula del conjunto de operaciones aplicables, o deviradas de la utilizacion de un rayo
 * en un entorno tridimensional.
 */
class Ray {
public:
    /**
        * @brief Inicializa el rayo apuntando en direccion al eje Z positivo (direccion hacia adelante)
        */
    Ray();
    
    /**
        * @brief Inicializa el rayo, usando un punto de base y una direccion arbitrarias
        */
    Ray(const exeng::math::Vector3f& point, 
        const exeng::math::Vector3f& direction);

    /**
        * @brief Establece el punto tomado como base del rayo.
        * @param point
        */
    void setPoint(const exeng::math::Vector3f& point);

    /**
        * @brief Devuelve el punto base del rayo.
        * @return 
        */
    exeng::math::Vector3f getPoint() const;
    
    /**
        * @brief Establece la direccion del rayo.
        * @param direction
        */
    void setDirection(const exeng::math::Vector3f& direction);
    
    /**
        * @brief Devuelve la direccion del rayo.
        * @return 
        */
    exeng::math::Vector3f getDirection() const;

    /**
        * @brief Calcula el punto que se encuentra a 't' unidades. 
        * 
        * Toma como base el punto base del rayo y la direccion.
        * Es posible que la distancia entre el punto base del rayo y el punto calculado por este
        * metodo es muy cercano a 't', por lo que a la hora de hacer comparaciones, es necesario
        * usar un valor de tolerancia 'epsilon'.
        * @param t
        * @return 
        */
    exeng::math::Vector3f getPointAt(float t) const;
    
    /**
        * @brief Establece los atributos del rayo.
        * @param point El punto base del rayo.
        * @param direction La direccion del rayo. 
        */
    void set(const exeng::math::Vector3f& point, 
                const exeng::math::Vector3f& direction);
    
private:
    exeng::math::Vector3f point;        //! Ray start point
    exeng::math::Vector3f direction;	//! Ray direction
};
}}

std::ostream& operator<< (std::ostream& os, const exeng::scenegraph::Ray& ray);


#include <cassert>

namespace exeng { namespace scenegraph {
    
inline Ray::Ray() : point(0.0f), direction(0.0, 0.0, 1.0f) { }

inline Ray::Ray(const exeng::math::Vector3f& point, const exeng::math::Vector3f& direction){
    this->set(point, direction);
}

inline void Ray::setPoint(const exeng::math::Vector3f& point){
    this->point = point;
}

inline exeng::math::Vector3f Ray::getPoint() const {
    return this->point;
}

inline void Ray::setDirection(const exeng::math::Vector3f& direction) {
    this->direction = direction;
    this->direction.normalize();
}

inline exeng::math::Vector3f Ray::getDirection() const {
    return this->direction;
}

inline exeng::math::Vector3f Ray::getPointAt(float t) const {
    assert( exeng::math::equals(this->direction.getMagnitude(), 1.0f) == true );
    
    auto p = this->point;
    auto d = this->direction;
    
    return p + t*d;
}


inline void Ray::set(const math::Vector3f &point, const math::Vector3f &direction) {
    this->setPoint(point);
    this->setDirection(direction);
}
        
}}


inline std::ostream& operator<< (std::ostream& os, const exeng::scenegraph::Ray& ray) {
    os << ray.getPoint() << ", " << ray.getDirection();
    return os;
}

#endif	//__EXENG_SCENEGRAPH_RAY_HPP__
