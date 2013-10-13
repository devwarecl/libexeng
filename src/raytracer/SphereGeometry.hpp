
#ifndef __RAYTRACER_SPHEREGEOMETRY_HPP__
#define __RAYTRACER_SPHEREGEOMETRY_HPP__

#include <exeng/scenegraph/Geometry.hpp>
#include <exeng/scenegraph/Sphere.hpp>
#include <exeng/math/TVector.hpp>

namespace raytracer {

/**
 * @brief Permite que agreguemos esferas al grafo de escena.
 */
class SphereGeometry : public exeng::scenegraph::Geometry {
public:
	SphereGeometry();
	SphereGeometry(float radius, const exeng::math::Vector3f &position);

	virtual ~SphereGeometry();
		
	virtual bool hit(const exeng::scenegraph::Ray &ray, exeng::scenegraph::IntersectInfo *intersectInfo);
		
	virtual exeng::math::Boxf getBox() const;

	exeng::scenegraph::Sphere sphere;	// La esfera
	exeng::graphics::Material material;	// El material de la esfera
};

}

#endif	//__RAYTRACER_SPHEREGEOMETRY_HPP__
