/**
 *	@brief Implementacion de la interfaz de rayos definida en Ray.hpp
 */

#include <cassert>

namespace exeng {
    namespace scenegraph {
		inline Ray::Ray() : point(0.0f), direction(0.0, 0.0, 1.0f) { }
        
		inline Ray::Ray(const exeng::math::Vector3f& point, const exeng::math::Vector3f& direction){
			this->setAttributes(point, direction);
		}

        inline void Ray::setPoint(const exeng::math::Vector3f& point){
            this->point = point;
        }
        
        inline exeng::math::Vector3f Ray::getPoint() const {
            return this->point;
        }
        
        inline void Ray::setDirection(const exeng::math::Vector3f& direction) {
            this->direction = direction;
            this->direction.normalize();
        }
        
        inline exeng::math::Vector3f Ray::getDirection() const {
            return this->direction;
        }
        
        inline exeng::math::Vector3f Ray::getPointAt(float t) const {
            assert( this->direction.getMagnitude() == 1.0 );
            
            auto p = this->point;
            auto d = this->direction;
            
            return p + t*d;
        }
        

        inline void Ray::setAttributes(const math::Vector3f &point, const math::Vector3f &direction) {
            this->setPoint(point);
            this->setDirection(direction);
        }


		inline auto Ray::setPoint(float x, float y, float z) -> void {
			this->point.set(x, y, z);
		}


		inline auto Ray::setPointX(float value) -> void {
			this->point.x = (value);
		}


		inline auto Ray::setPointY(float value) -> void {
			this->point.y = (value);
		}

		inline auto Ray::setPointZ(float value) -> void {
			this->point.z = (value);
		}

		inline auto Ray::getPointX() const -> float {
			return this->point.x;
		}

		inline auto Ray::getPointY() const -> float {
			return this->point.y;
		}


		inline auto Ray::getPointZ() const -> float {
			return this->point.z;
		}


		inline auto Ray::setDirection(float x, float y, float z) -> void {
			this->direction.set(x, y, z);
			this->direction.normalize();
		}

		/*
		inline auto Ray::setDirectionX(float value) -> void{
			this->direction.x = (value);
		}

        inline auto Ray::setDirectionY(float value) -> void {
			this->direction.y = (value);
		}

        inline auto Ray::setDirectionZ(float value) -> void {
			this->direction.z = (value);
		}
		*/

		inline auto Ray::getDirectionX() const -> float {
			return this->direction.x;
		}

        inline auto Ray::getDirectionY() const -> float {
			return this->direction.y;
		}

        inline auto Ray::getDirectionZ() const -> float {
			return this->direction.z;
		}
    }
}


inline std::ostream& operator<< (std::ostream& os, const exeng::scenegraph::Ray& ray) {
	os << ray.getPoint() << ", " << ray.getDirection();
	return os;
}
