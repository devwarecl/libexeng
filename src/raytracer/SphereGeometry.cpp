
#include "SphereGeometry.hpp"
#include <algorithm>

namespace RayTracer {
	SphereGeometry::SphereGeometry() {}
	SphereGeometry::~SphereGeometry() {}
	
	SphereGeometry::SphereGeometry(float radius, const exeng::math::Vector3f &position) {
		this->sphere.setAttributes(radius, position);
	}


	bool SphereGeometry::hit(const exeng::scenegraph::Ray &ray, exeng::scenegraph::IntersectInfo *intersectInfo) {
		bool result = this->sphere.intersect(ray, intersectInfo);

		if (result == true) {
			intersectInfo->surfaceMaterial = &this->material;
		}

		return result;
	}


	exeng::math::Boxf SphereGeometry::getBoundingBox() const {
		auto halfRadius = 0.5f * this->sphere.getRadius();
		auto point = exeng::math::Vector3f(halfRadius);
		
		return exeng::math::Boxf(-point, point);
	}
}
