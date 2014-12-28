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

namespace exeng { namespace scenegraph {
    
    inline Plane::Plane() : point(0.0f), normal(0.0f, 1.0, 0.0f) {}


    inline Plane::Plane(const exeng::Vector3f& point, const exeng::Vector3f& normal) {
        this->set(point, normal);
    }


    inline Plane::Plane(const exeng::Vector3f& p1, const exeng::Vector3f& p2, const exeng::Vector3f& p3) {   
        this->set(p1, p2, p3);
    }


    inline void Plane::set(const exeng::Vector3f& point, const exeng::Vector3f& normal) {
        this->setPoint(point);
        this->setNormal(normal);
    }


    inline void Plane::set(const exeng::Vector3f& p1, const exeng::Vector3f& p2, const exeng::Vector3f& p3) {
        const float factor = 1.0f/3.0f;
		
        exeng::Vector3f normal = cross(p2 - p1, p3 - p1);
        exeng::Vector3f point = factor * (p1 + p2 + p3);
		
        this->set(point, normal);
    }


    inline void Plane::setNormal(const exeng::Vector3f& normal) {
        this->normal = normalize(normal);
    }


    inline void Plane::setPoint(const exeng::Vector3f& point) {
        this->point = point;
    }


    inline exeng::Vector3f Plane::getNormal() const {
        return this->normal;
    }


    inline exeng::Vector3f Plane::getPoint() const {
        return this->point;
    }

    inline bool Plane::intersect(const Ray& ray, IntersectInfo* intersectInfo) const {
        auto p = this->point;
        auto n = this->normal;
    
        auto r = ray.getPoint();
        auto d = ray.getDirection();
    
        auto t = dot(n, p - r) / dot(n, d);
		
        bool result = false;
    
        if (t > 0.0f) {
            result = true;
        }
    
        if (intersectInfo) {
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
