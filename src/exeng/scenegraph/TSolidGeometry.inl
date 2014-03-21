
#include <exeng/scenegraph/Box.hpp>
#include <exeng/scenegraph/Intersect.hpp>

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
    exeng::math::Boxf TSolidGeometry<Solid>::getBox() const {
        return box(this->solid);
    }
}}
