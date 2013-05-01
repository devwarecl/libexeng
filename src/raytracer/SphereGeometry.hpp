
#ifndef __RAYTRACER_SPHEREGEOMETRY_HPP__
#define __RAYTRACER_SPHEREGEOMETRY_HPP__

#include <exeng/scenegraph/Geometry.hpp>
#include <exeng/scenegraph/Sphere.hpp>
#include <exeng/math/TVector.hpp>

namespace raytracer {
	/**
	 * 	@brief Permite que agreguemos esferas al grafo de escena.
	 */
	class SphereGeometry : public exeng::scenegraph::Geometry {
	public:
		/**
		 * 	@brief Constructor por defecto
		 */
		SphereGeometry();


		SphereGeometry(float radius, const exeng::math::Vector3f &position);


		/**
		 * 	@brief
		 */
		virtual ~SphereGeometry();
		
		/**
		 * 	@brief Intersecta la esfera con el rayo indicado.
		 */
		virtual bool hit(const exeng::scenegraph::Ray &ray, exeng::scenegraph::IntersectInfo *intersectInfo);
		
		/**
		 * 	@brief Devuelve la caja de colision de la esfera
		 */
		virtual exeng::math::Boxf getBox() const;

		exeng::scenegraph::Sphere sphere;	// La esfera
		exeng::graphics::Material material;	// El material de la esfera
	};

}

#endif	//__RAYTRACER_SPHEREGEOMETRY_HPP__
