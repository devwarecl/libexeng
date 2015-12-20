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

#ifndef __EXENG_SCENEGRAPH_SPHERE_HPP__
#define __EXENG_SCENEGRAPH_SPHERE_HPP__

#include <xe/Vector.hpp>
#include <xe/sg/Ray.hpp>
#include <xe/sg/IntersectInfo.hpp>

namespace xe { namespace sg {

	class Ray;
	struct IntersectInfo;

	/**
		* @brief Esfera en el espacio tridimensional.
		*/
	class Sphere {
	public:
		Sphere();
    
		/**
		 * @brief Inicializa una esfera en el origen, y con radio arbitrario
		 */
		explicit Sphere(float radius);
    
		/**
		 * @brief Inicializa una esfera cuyo centro este en la posicion y con el radio indicados.
		 * @param radius El radio de la esfera, en unidades de mundo.
		 * @param center La posicion en el espacio, en donde estara ubicado el centro de la esfera.
		 */
		explicit Sphere(float radius, const xe::Vector3f &center);
    
		/**
		 * @brief Inicializa todos los atributos de la esfera de una sola vez.
		 */
		void setAttributes(float radius, const xe::Vector3f &center);
    
		/**
		 * @brief Establece el radio de la esfera
		 */
		void setRadius(float radius);
    
		/**
		 * @brief Establece la posicion en donde estara ubicado el centro de la esfera.
		 */
		void setCenter(const xe::Vector3f &center);
    
		/**
		 * @brief Devuelve el radio actual de la esfera
		 */
		float getRadius() const;
    
		/**
		 * @brief Devuelve la posicion en donde esta ubicado el centro de la esfera
		 */
		xe::Vector3f getCenter() const;
    
		/**
		 * @brief Calcula la interseccion entre el rayo indicado, y la esfera.
		 */
		bool intersect(const Ray& ray, IntersectInfo *intersectInfo=nullptr) const;
    
		/**
		 * @brief Comprueba si dos esferas son iguales.
		 */
		bool operator== (const Sphere &sphere) const;
    
		/**
		 * @brief Comprueba si dos esferas son distintas.
		 */
		bool operator!= (const Sphere &sphere) const;
    
	private:
		xe::Vector3f center;
		float radius;

		friend std::ostream& operator<< (std::ostream &os, const xe::sg::Sphere &sphere)
		{
			std::cout << sphere.getCenter() << ", " << sphere.getRadius();
			return os;
		}
	};


	inline Sphere::Sphere() {
		this->setAttributes(1.0f, xe::Vector3f(0.0));
	}


	inline Sphere::Sphere(float radius) {
		this->setAttributes(radius, xe::Vector3f(0.0));
	}


	inline Sphere::Sphere(float radius, const xe::Vector3f &center) {
		this->setAttributes(radius, center);
	}


	inline void Sphere::setAttributes(float radius, const xe::Vector3f &center){
		this->setRadius(radius);
		this->setCenter(center);
	}


	inline auto Sphere::setRadius(float radius) -> void {
		if (radius < 0.0f) {
			radius = 0.0;
		}
    
		this->radius = radius;
	}


	inline void Sphere::setCenter(const xe::Vector3f &center) {
		this->center = center;
	}


	inline float Sphere::getRadius() const {
		return this->radius;
	}


	inline xe::Vector3f Sphere::getCenter() const{
		return this->center;
	}


	inline bool Sphere::intersect(const Ray& ray, IntersectInfo *intersectInfo) const {
    
		// Variables de apoyo al algoritmo
		float t;
		bool result = false;

		// Variables del modelo matematico
		auto r0 = ray.getPoint();
		auto d = ray.getDirection();

		auto c = this->getCenter();
		auto r = this->getRadius();

		// Temporales para ahorrar calculos
		auto r_2 = r*r;

		auto r0_sub_c = r0 - c;
		auto r0_c_2 = abs2(r0_sub_c);

		// Temporales de la ecuacion cuadratica
		auto B = 2.0f * dot(d, r0_sub_c);
		auto C = r0_c_2 - r_2;

		// Calcular el discriminante
		auto disc = B*B - 4.0f*C;
    
		if (disc == 0.0f) {
			// Solo existe un punto de interseccion (el rayo es tangente a la esfera)
			t = -B / 2.0f;
        
			// Ver si el punto esta "adelante" del rayo, y no detras
			if (t > 0.0f) {
				result = true;
			}
		} else if (disc > 0.0f) {
			// Existen dos puntos de interseccion 
			auto rootDisc = std::sqrt(disc);

			// Determinar el primer punto de interseccion
			float t1 = ( -B - rootDisc ) / 2.0f;
			float t2 = ( -B + rootDisc ) / 2.0f;
        
			t = std::min(t1, t2);

			if (t > 0.0f) {
				result = true;
			}
		} else {
			// El rayo no toca a la esfera, ni por delante no por detras (caso mas comun)
			result = false;
		}
    
		// Rellenar la estructura con la informacion sobre las colisiones
		if (intersectInfo != nullptr) {
			intersectInfo->intersect = result;

			if (intersectInfo->intersect == true) {
				intersectInfo->normal = normalize(ray.getPointAt(t));
				intersectInfo->distance = t;
			}
		}
    
		return result;
	}


	inline bool Sphere::operator== (const Sphere &sphere) const {
		if (this->getCenter() != sphere.getCenter()) {
			return false;
		}
    
		if (this->getRadius() != sphere.getRadius()) {
			return false;
		}
    
		return true;
	}


	inline bool Sphere::operator!= (const Sphere &sphere) const {
		return ! (*this == sphere);
	}  

}}

#endif  //__EXENG_SCENEGRAPH_SPHERE_HPP__
