/**
 * @file Intersect.hpp
 * @brief Intersection routines for different elemental objects.
 */

#ifndef __EXENG_SCENEGRAPH_TSOLIDGEOMETRY_HPP__
#define __EXENG_SCENEGRAPH_TSOLIDGEOMETRY_HPP__

#include <exeng/scenegraph/Geometry.hpp>

namespace exeng { namespace scenegraph {
    template<typename Solid>
    class TSolidGeometry : public Geometry {
    public:
        TSolidGeometry();
        TSolidGeometry(const Solid &solid_, const exeng::graphics::Material* material_);
        
        virtual bool hit(const Ray &ray, IntersectInfo *intersectInfo);
        virtual exeng::math::Boxf getBox() const;
    
    public:
        Solid solid;
        const exeng::graphics::Material* material;
    };
}}

#include <exeng/scenegraph/TSolidGeometry.inl>

#endif  //__EXENG_SCENEGRAPH_TSOLIDGEOMETRY_HPP__
