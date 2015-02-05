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

#include <exeng/Vector.hpp>
#include <exeng/scenegraph/Ray.hpp>
#include <exeng/scenegraph/IntersectInfo.hpp>

namespace exeng { namespace scenegraph {
    
class Ray;
struct IntersectInfo;

/**
 * @brief Plane on 3-space.
 */
class Plane {
public:
    /**
     * @brief Initialize a plane on the X-Z plane, pointing on the positive Y-Axis.
     */
    Plane();
    
    Plane(const exeng::Vector3f& point, const exeng::Vector3f& normal);
    
    /**
     * @brief Initialize a plane from three coplanar points.
     */
    Plane(const exeng::Vector3f& p1, const exeng::Vector3f& p2, const exeng::Vector3f& p3);
    
    /**
     * @brief Rebuild a plane from a central point and a normal vector.
     */
    void set(const exeng::Vector3f& point, const exeng::Vector3f& normal);
    
    /**
     * @brief Rebuild the current plane from three coplanar points.
     */
    void set(const exeng::Vector3f& p1, const exeng::Vector3f& p2, const exeng::Vector3f& p3);
    
    /**
     * @brief Change the normal of the current plane, and normalizes the incoming vector before mutating it.
     */
    void setNormal(const exeng::Vector3f& normal);
    
    /**
     * @brief Get the current normal of the current plane. This vector is always normalized.
     */
    exeng::Vector3f getNormal() const;
    
    /**
     * @brief Changes the base point of the current plane.
     */
    void setPoint(const exeng::Vector3f& point);
    
    /**
     * @brief Get the current point of the current plane.
     */
    exeng::Vector3f getPoint() const;
    
    /**
     * @brief Check if the current plane intersects with the 
     */
    bool intersect(const Ray& ray, IntersectInfo* intersectInfo=nullptr) const;
    
private:
    exeng::Vector3f point;
    exeng::Vector3f normal;
};

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

std::ostream& operator<< (std::ostream& os, const exeng::scenegraph::Plane &plane);

inline std::ostream& operator<< (std::ostream& os, const exeng::scenegraph::Plane &plane) {
    return os << "Point : {" << plane.getPoint() << "}, Normal : {" << plane.getNormal() << "}";
}


#endif	//__EXENG_SCENEGRAPH_PLANE_HPP__
