/**
 * @file Triangle.hpp
 * @brief Defines the Triangle structure
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_SCENEGRAPH_TRIANGLE_HPP__
#define __EXENG_SCENEGRAPH_TRIANGLE_HPP__

#include <exeng/scenegraph/Plane.hpp>
#include <exeng/scenegraph/Ray.hpp>
#include <exeng/scenegraph/IntersectInfo.hpp>

namespace exeng { namespace scenegraph {
    template<typename VectorType>
    struct Triangle {
        const VectorType &p1;
        const VectorType &p2;
        const VectorType &p3;
        
        Triangle(const VectorType &p1, const VectorType &p2, const VectorType &p3);
        
        VectorType getNormal() const;
        
        VectorType getNormalUnnormalized() const;
        
        bool hit(const Ray& ray, IntersectInfo *info=nullptr) const;
    };
}}

#include <exeng/scenegraph/Triangle.inl>

#endif  //__EXENG_SCENEGRAPH_TRIANGLE_HPP__
