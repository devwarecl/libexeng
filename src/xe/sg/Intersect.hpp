/**
 * @file Intersect.hpp
 * @brief Intersection routines for different elemental objects.
 */

#ifndef __EXENG_SCENEGRAPH_INTERSECT_HPP__
#define __EXENG_SCENEGRAPH_INTERSECT_HPP__

#include <xe/Boundary.hpp>
#include <xe/sg/IntersectInfo.hpp>
#include <xe/sg/Ray.hpp>
#include <xe/sg/Sphere.hpp>
#include <xe/sg/Plane.hpp>

#if defined(_WIN32)
#  pragma push_macro("max")
#  pragma push_macro("near")
#  pragma push_macro("far")
#  undef max
#  undef near
#  undef far
#endif

#include <limits>

namespace xe { namespace sg {
    bool intersect(const Ray &ray, const Boxf &box, IntersectInfo *info);
    bool intersect(const Ray &ray, const Plane &plane, IntersectInfo *info);
    bool intersect(const Ray &ray, const Sphere &sphere, IntersectInfo *info);

	inline bool intersect(const Ray &ray, const xe::Boxf &box, IntersectInfo *info) 
	{
        Vector3f minEdge = box.getMin();
        Vector3f maxEdge = box.getMax();
        
        Vector3f rayPoint = ray.getPoint();
        Vector3f rayDirection = ray.getDirection();
        
        float near = -std::numeric_limits<float>::max();
        float far = std::numeric_limits<float>::max();
        
        // For each coord, get the near and far intersection distances
        for (int coord=0; coord<3; ++coord) {
            
            // Ray is parallel to current coordinate
            if (rayDirection[coord] == 0.0f) { 
                if (rayPoint[coord] < minEdge[coord] || rayPoint[coord] > maxEdge[coord]) {
                    if ( info != nullptr ) {
                        info->intersect = false;
                    }
                    
                    return false;
                }
                
                continue;
            }
            
            // Ray is not parallel. Continue compute of the intersection
            float invRayDirection = 1.0f / rayDirection[coord];
            float t1 = (minEdge[coord] - rayPoint[coord]) * invRayDirection;
            float t2 = (maxEdge[coord] - rayPoint[coord]) * invRayDirection;
            
            if (t1 > t2) {
                std::swap(t1, t2);
            }
            
            if (t1 > near) {
                near = t1;
            }
            
            if (t2 < far) {
                far = t2;
            }
            
            if (near > far) {
                if (info != nullptr) {
                    info->intersect = false;
                }
                
                return false;
            }
            
            if (far < 0.0f) {
                if (info != nullptr) {
                    info->intersect = false;
                }
                
                return false;
            }
        }
        
        // Compute intersection point
        if (info != nullptr) {
            info->intersect = true;
            info->point = ray.getPointAt(near);
            
            // Compute face normal
            info->normal = Vector3f::zero();
            
            const float epsilon = 0.0001f;
            
            for (int coord=0; coord<3; ++coord) {
                if (abs(info->point[coord] - minEdge[coord]) <= epsilon) {
                    info->normal[coord] = -1.0f;
                    break;
                }
                
                if (abs(info->point[coord] - maxEdge[coord]) <= epsilon) {
                    info->normal[coord] = 1.0f;
                    break;
                }
            }
            
            info->distance = near;
        }
        
        return true;
    }
    
    inline bool intersect(const Ray &ray, const Plane &plane, IntersectInfo *info) 
	{
        return plane.intersect(ray, info);
    }
    
    inline bool intersect(const Ray &ray, const Sphere &sphere, IntersectInfo *info) 
	{
        return sphere.intersect(ray, info);
    }
}}

#if defined(_WIN32)
#  pragma pop_macro("max")
#  pragma pop_macro("near")
#  pragma pop_macro("far")
#endif

#endif  //__EXENG_SCENEGRAPH_INTERSECT_HPP__
