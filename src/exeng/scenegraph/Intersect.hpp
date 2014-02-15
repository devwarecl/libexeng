/**
 * @file Intersect.hpp
 * @brief Intersection routines for different elemental objects.
 */

#ifndef __EXENG_SCENEGRAPH_INTERSECT_HPP__
#define __EXENG_SCENEGRAPH_INTERSECT_HPP__

#include <exeng/math/TBoundary.hpp>
#include <exeng/scenegraph/IntersectInfo.hpp>
#include <exeng/scenegraph/Ray.hpp>
#include <exeng/scenegraph/Sphere.hpp>
#include <exeng/scenegraph/Plane.hpp>

namespace exeng { namespace scenegraph {
    bool intersect(const Ray &ray, const exeng::math::Boxf &box, IntersectInfo *info);
    bool intersect(const Ray &ray, const Plane &plane, IntersectInfo *info);
    bool intersect(const Ray &ray, const Sphere &sphere, IntersectInfo *info);
}}


#include <exeng/scenegraph/Intersect.inl>

#endif  //__EXENG_SCENEGRAPH_INTERSECT_HPP__
