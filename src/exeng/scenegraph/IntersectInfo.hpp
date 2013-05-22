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

#include <exeng/math/TVector.hpp>
#include <exeng/graphics/Material.hpp>

namespace exeng {
    namespace scenegraph {
        /**
         * @brief Store information about the intersection between a ray and a object.
         */
        struct EXENGAPI IntersectInfo {
        public:
            //! Intersection state. If false, the other attributes are on a unspecified state.
            bool intersect;                                 
            
            //! Distance from the ray starting point to the point of intersection.
            float distance;                                 
            
            //! Surface normal at the intersection point.
			exeng::math::Vector3f normal;                   
            
            //! Ray - surface intersection point.
            exeng::math::Vector3f point;                    
            
            //! Surface material.
			const exeng::graphics::Material* materialPtr;   

        public:
			IntersectInfo();
        };
    }
}

#endif  //__EXENG_SCENEGRAPH_INTERSECTINFO_HPP__
