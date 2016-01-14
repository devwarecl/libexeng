
#include "TMap.hpp"

namespace lw {
	TMap::TMap() {}
	TMap::TMap(::lwTMap *value) : Collection<TMap, ::lwTMap>(value) {}

	VParam TMap::center() const {
		return VParam(&this->value->center);
	}

	VParam TMap::rotate() const {
		return VParam(&this->value->rotate);
	}

	VParam TMap::size() const {
		return VParam(&this->value->size);
	}

	xe::Vector3f TMap::map_texcoord(Proj::Enum projection, const xe::Vector3f &point) {
		const xe::Vector3f center = this->center().val();
		const xe::Vector3f ypr = this->rotate().val();
		const xe::Vector3f size = this->size().val();

		xe::Vector3f q = point - center;

		q = xe::transform(xe::rotate<float>(ypr.z, { 0.0f, 0.0f, -1.0f}), q);
		q = xe::transform(xe::rotate<float>(ypr.y, { 0.0f, 1.0f,  0.0f}), q);
		q = xe::transform(xe::rotate<float>(ypr.x, {-1.0f, 0.0f,  0.0f}), q);

		if (projection != Proj::Spherical) {
			q = q / size;
		}

		return q;
	}
}
