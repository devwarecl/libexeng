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
    return os << "Point : {" << ray.getPoint() << "}, Direction : {" << ray.getDirection() << "}";
}
