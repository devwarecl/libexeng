
#include "SphereGeometry.hpp"
#include <algorithm>

using exeng::scenegraph::Ray;
using exeng::scenegraph::IntersectInfo;
using exeng::math::Vector3f;
using exeng::math::Boxf;


namespace raytracer {
	SphereGeometry::SphereGeometry() {}
	SphereGeometry::~SphereGeometry() {}
	
	SphereGeometry::SphereGeometry(float radius, const Vector3f &position) {
		this->sphere.setAttributes(radius, position);
	}


	bool SphereGeometry::hit(const Ray &ray, IntersectInfo *intersectInfo) {
		bool result = this->sphere.intersect(ray, intersectInfo);

		if (result == true) {
			intersectInfo->surfaceMaterial = &this->material;
		}

		return result;
	}


	Boxf SphereGeometry::getBoundingBox() const {
		auto halfRadius = 0.5f * this->sphere.getRadius();
		auto point = Vector3f(halfRadius);
		
		return Boxf(-point, point);
	}
}
