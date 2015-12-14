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

#ifndef __EXENG_SCENEGRAPH_RAY_HPP__
#define __EXENG_SCENEGRAPH_RAY_HPP__

#include <iosfwd>
#include <cassert>

#include <exeng/Config.hpp>
#include <exeng/Vector.hpp>

namespace exeng { namespace scenegraph { 
    
	/**
	 * @brief Ray abstraction.
	 */
	class Ray {
	public:
		/**
		 * @brief Initializes the ray, positioned around the origin, and pointing in the positive Z-axis.
		 */
		Ray();
    
		/**
		 * @brief Initialize the ray, orientated around a arbitrary origin and direction.
		 */
		Ray(const exeng::Vector3f& point, const exeng::Vector3f& direction);

		/**
		 * @brief Set the starting point of the ray.
		 */
		void setPoint(const exeng::Vector3f& point);

		/**
		 * @brief Get the starting point of the ray.
		 */
		exeng::Vector3f getPoint() const;
    
		/**
		 * @brief Set the direction of the ray. The vector of direction is normalized before mutates the Ray object.
		 */
		void setDirection(const exeng::Vector3f& direction);
    
		/**
		 * @brief Get the direction of the ray. This vector is always normalized.
		 */
		exeng::Vector3f getDirection() const;
    
		/**
		 * @brief Computes the point of the ray at 't' distance from the starting point, to the 
		 * direction of the ray.
		 */
		exeng::Vector3f getPointAt(float t) const;
    
		/**
		 * @brief Set the starting point and the direction of the ray in one method call.
		 */
		void set(const exeng::Vector3f& point, const exeng::Vector3f& direction);
    
	private:
		exeng::Vector3f point;
		exeng::Vector3f direction;
	};

}}

std::ostream& operator<< (std::ostream& os, const exeng::scenegraph::Ray& ray);


namespace exeng { namespace scenegraph {

	inline Ray::Ray() : point(0.0f), direction(0.0, 0.0, 1.0f) { }

	inline Ray::Ray(const exeng::Vector3f& point, const exeng::Vector3f& direction){
		this->set(point, direction);
	}

	inline void Ray::setPoint(const exeng::Vector3f& point){
		this->point = point;
	}

	inline exeng::Vector3f Ray::getPoint() const {
		return this->point;
	}

	inline void Ray::setDirection(const exeng::Vector3f& direction) {
		this->direction = normalize(direction);
	}

	inline exeng::Vector3f Ray::getDirection() const {
		return this->direction;
	}

	inline exeng::Vector3f Ray::getPointAt(float t) const {
		assert( exeng::equals( exeng::abs(this->direction), 1.0f) == true );
    
		auto p = this->point;
		auto d = this->direction;
    
		return p + t*d;
	}


	inline void Ray::set(const Vector3f &point, const Vector3f &direction) {
		this->setPoint(point);
		this->setDirection(direction);
	}
        
}}


inline std::ostream& operator<< (std::ostream& os, const exeng::scenegraph::Ray& ray) {
    return os << "Point : {" << ray.getPoint() << "}, Direction : {" << ray.getDirection() << "}";
}


#endif	//__EXENG_SCENEGRAPH_RAY_HPP__
