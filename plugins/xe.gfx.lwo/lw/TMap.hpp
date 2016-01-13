
#pragma once

namespace lw {
	class TMap : public Collection<TMap, ::lwTMap> {
	public:
		TMap() {}
		explicit TMap(::lwTMap *value) : Collection<TMap, ::lwTMap>(value) {}

		VParam center() const {
			return VParam(&this->value->center);
		}

		VParam rotate() const {
			return VParam(&this->value->rotate);
		}

		VParam size() const {
			return VParam(&this->value->size);
		}

		xe::Vector3f setupTexturePoint(const xe::Vector3f &point, Proj::Enum proj) {
			const xe::Vector3f center = this->center().val();
			const xe::Vector3f ypr = this->rotate().val();
			const xe::Vector3f size = this->size().val();

			xe::Vector3f q = point - center;

			q = xe::transform(xe::rotate<float>(ypr.z, { 0.0f, 0.0f, -1.0f}), q);
			q = xe::transform(xe::rotate<float>(ypr.y, { 0.0f, 1.0f,  0.0f}), q);
			q = xe::transform(xe::rotate<float>(ypr.x, {-1.0f, 0.0f,  0.0f}), q);

			if (proj != Proj::Spherical) {
				q = q / size;
			}

			return q;
		}
	};
}
