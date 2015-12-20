/**
 * @file IntersectInfo.hpp
 * @brief IntersectInfo structure interface definition.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_SCENEGRAPH_INTERSECTINFO_HPP__
#define __EXENG_SCENEGRAPH_INTERSECTINFO_HPP__

#include <xe/Vector.hpp>
#include <xe/gfx/Material.hpp>

namespace xe { namespace sg {
    /**
     * @brief Store information about the intersection between a ray and a object.
     */
    struct IntersectInfo {
    public:
        //! Intersection state. If false, the other attributes are on a unspecified state.
        bool intersect;                                 
        
        //! Distance from the ray starting point to the point of intersection.
        float distance;                                 
        
        //! Surface normal at the intersection point.
        xe::Vector3f normal;                   
        
        //! Ray - surface intersection point.
        xe::Vector3f point;                    
        
        //! Surface material.
        const xe::gfx::Material* material;   
    
    public:
        IntersectInfo();
    };
}}

namespace xe { namespace sg {
    inline IntersectInfo::IntersectInfo() {
        this->intersect = false;
        this->distance = 0.0f;
        this->normal = xe::Vector3f(0.0f);
        this->point = xe::Vector3f(0.0f);
        this->material = nullptr;
    } 
}}


#endif  //__EXENG_SCENEGRAPH_INTERSECTINFO_HPP__
