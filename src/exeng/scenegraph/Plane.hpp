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
 * @brief Plane on 3-space.
 */
class Plane {
public:
    /**
     * @brief Initialize a plane on the X-Z plane, pointing on the positive Y-Axis.
     */
    Plane();
    
    Plane(const exeng::math::Vector3f& point, const exeng::math::Vector3f& normal);
    
    /**
     * @brief Initialize a plane from three coplanar points.
     */
    Plane(const exeng::math::Vector3f& p1, const exeng::math::Vector3f& p2, const exeng::math::Vector3f& p3);
    
    /**
     * @brief Rebuild a plane from a central point and a normal vector.
     */
    void set(const exeng::math::Vector3f& point, const exeng::math::Vector3f& normal);
    
    /**
     * @brief Rebuild the current plane from three coplanar points.
     */
    void set(const exeng::math::Vector3f& p1, const exeng::math::Vector3f& p2, const exeng::math::Vector3f& p3);
    
    /**
     * @brief Change the normal of the current plane, and normalizes the incoming vector before mutating it.
     */
    void setNormal(const exeng::math::Vector3f& normal);
    
    /**
     * @brief Get the current normal of the current plane. This vector is always normalized.
     */
    exeng::math::Vector3f getNormal() const;
    
    /**
     * @brief Changes the base point of the current plane.
     */
    void setPoint(const exeng::math::Vector3f& point);
    
    /**
     * @brief Get the current point of the current plane.
     */
    exeng::math::Vector3f getPoint() const;
    
    /**
     * @brief Check if the current plane intersects with the 
     */
    bool intersect(const Ray& ray, IntersectInfo* intersectInfo=nullptr) const;
    
private:
    exeng::math::Vector3f point;
    exeng::math::Vector3f normal;
};

}}

std::ostream& operator<< (std::ostream& os, const exeng::scenegraph::Plane &plane);

#include "Plane.inl"

#endif	//__EXENG_SCENEGRAPH_PLANE_HPP__
