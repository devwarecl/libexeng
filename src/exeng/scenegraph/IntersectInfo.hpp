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

#include <exeng/Vector.hpp>
#include <exeng/graphics/Material.hpp>

namespace exeng { namespace scenegraph {
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
        exeng::Vector3f normal;                   
        
        //! Ray - surface intersection point.
        exeng::Vector3f point;                    
        
        //! Surface material.
        const exeng::graphics::Material* material;   
    
    public:
        IntersectInfo();
    };
}}

namespace exeng { namespace scenegraph {
    inline IntersectInfo::IntersectInfo() {
        this->intersect = false;
        this->distance = 0.0f;
        this->normal = exeng::Vector3f(0.0f);
        this->point = exeng::Vector3f(0.0f);
        this->material = nullptr;
    } 
}}


#endif  //__EXENG_SCENEGRAPH_INTERSECTINFO_HPP__
