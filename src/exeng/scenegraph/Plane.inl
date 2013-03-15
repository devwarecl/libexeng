/**
 * @brief Implementa los metodos de la clase de planos
 */

namespace exeng {
    namespace scenegraph {
        inline Plane::Plane() {
            this->set( exeng::math::Vector3f(0.0), exeng::math::Vector3f(0.0f, 1.0f, 0.0f) );
        }
        
        
        inline Plane::Plane(const exeng::math::Vector3f& point, const exeng::math::Vector3f& normal) {
            this->set(point, normal);
        }
    
        
        inline void Plane::set(const exeng::math::Vector3f& point, const exeng::math::Vector3f& normal) {
            this->setPoint(point);
            this->setNormal(normal);
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
        
        
        inline auto Plane::intersect(const Ray& ray, IntersectInfo* intersectInfo) -> bool {
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
                intersectInfo->parametricCoord = t;
            }
            
            return result;
        }
    }
}
