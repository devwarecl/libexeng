
#include "SphereGeometry.hpp"
#include <algorithm>

using namespace exeng;
using namespace exeng::scenegraph;
using namespace exeng::math;

namespace raytracer {
	SphereGeometry::SphereGeometry() {}
	SphereGeometry::~SphereGeometry() {}
	
	SphereGeometry::SphereGeometry(float radius, const Vector3f &position) {
		this->sphere.setAttributes(radius, position);
	}


	bool SphereGeometry::hit(const Ray &ray, IntersectInfo *intersectInfo) {
		bool result = this->sphere.intersect(ray, intersectInfo);

		if (result == true) {
			intersectInfo->materialPtr = &this->material;
		}

		return result;
	}


	Boxf SphereGeometry::getBox() const {
		auto halfRadius = 0.5f * this->sphere.getRadius();
		auto point = Vector3f(halfRadius);
		
		return Boxf(-point, point);
	}
}
