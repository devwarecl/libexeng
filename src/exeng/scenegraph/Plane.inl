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


namespace exeng {
    namespace scenegraph {
        inline Plane::Plane() {
            this->set( exeng::math::Vector3f(0.0), exeng::math::Vector3f(0.0f, 1.0f, 0.0f) );
        }
        
        
        inline Plane::Plane(const exeng::math::Vector3f& point, const exeng::math::Vector3f& normal) {
            this->set(point, normal);
        }
        
        
        inline Plane::Plane(const exeng::math::Vector3f& p1, const exeng::math::Vector3f& p2, const exeng::math::Vector3f& p3) {   
            this->set(p1, p2, p3);
        }
        
        
        inline void Plane::set(const exeng::math::Vector3f& point, const exeng::math::Vector3f& normal) {
            this->setPoint(point);
            this->setNormal(normal);
        }
    
    
        inline void Plane::set(const exeng::math::Vector3f& p1, 
                               const exeng::math::Vector3f& p2, 
                               const exeng::math::Vector3f& p3) {
            
            exeng::math::Vector3f v1 = p2 - p1;
            exeng::math::Vector3f v2 = p3 - p1;
            
            exeng::math::Vector3f normal = v1.cross(v2);
            exeng::math::Vector3f point = (1.0f/3.0f) * (p1 + p2 + p3);
            
            this->set(point, normal);
        }
        
        
        inline void Plane::setNormal(const exeng::math::Vector3f& normal) {
            this->normal = normal;
            this->normal.normalize();
        }
    
        
        inline void Plane::setPoint(const exeng::math::Vector3f& point) {
            this->point = point;
        }
    
        
        inline exeng::math::Vector3f Plane::getNormal() const {
            return this->normal;
        }
        
        
        inline exeng::math::Vector3f Plane::getPoint() const {
            return this->point;
        }
        
        
        inline bool Plane::intersect(const Ray& ray, IntersectInfo* intersectInfo) {
            using namespace exeng::math;
            
            auto p = this->point;
            auto n = this->normal;
            
            auto r = ray.getPoint();
            auto d = ray.getDirection();
            
            auto t = n.dot(r - p) /  n.dot(d);
            
            bool result = true;
            
            if (t > 0.0f) {
                result = true;
            } else {
                result = false;
            }
            
            if (intersectInfo != nullptr) {
                intersectInfo->intersect = result;
                intersectInfo->distance = t;
            }
            
            return result;
        }
    }
}
