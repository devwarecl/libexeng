/**
 * @file Intersect.hpp
 * @brief Intersection routines for different elemental objects.
 */

#ifndef __EXENG_SCENEGRAPH_TSOLIDGEOMETRY_HPP__
#define __EXENG_SCENEGRAPH_TSOLIDGEOMETRY_HPP__

#include <exeng/scenegraph/Geometry.hpp>
#include <exeng/scenegraph/Box.hpp>
#include <exeng/scenegraph/Intersect.hpp>

namespace exeng { namespace scenegraph {
    template<typename Solid>
    class TSolidGeometry : public Geometry {
    public:
        TSolidGeometry();
        TSolidGeometry(const Solid &solid_, const exeng::graphics::Material* material_);
        
        virtual bool hit(const Ray &ray, IntersectInfo *intersectInfo);
        virtual Boxf getBox() const;
    
    public:
        Solid solid;
        const exeng::graphics::Material* material;
    };
}}

namespace exeng { namespace scenegraph {
    template<typename Solid>
    TSolidGeometry<Solid>::TSolidGeometry() : material(nullptr) {}
        
    template<typename Solid>
    TSolidGeometry<Solid>::TSolidGeometry(const Solid &solid_, const exeng::graphics::Material* material_) : solid(solid_), material(material_) {}
    
    template<typename Solid>
    bool TSolidGeometry<Solid>::hit(const Ray &ray, IntersectInfo *intersectInfo) {
        bool intersection = intersect(ray, this->solid, intersectInfo);
        
        if (intersection==true && intersectInfo!=nullptr) {
            intersectInfo->material = this->material;
        }
        
        return intersection;
    }
    
    
    template<typename Solid>
    Boxf TSolidGeometry<Solid>::getBox() const {
        return box(this->solid);
    }
}}

#endif  //__EXENG_SCENEGRAPH_TSOLIDGEOMETRY_HPP__
