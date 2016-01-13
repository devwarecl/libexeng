
#pragma once

namespace lw {
	
	class RMap : public Wrapper<RMap, ::lwRMap> {
	public:
		RMap() {}
		RMap(::lwRMap *value) : Wrapper<RMap, ::lwRMap>(value) {}

		int cindex() const {
			return this->value->cindex;
		}

		int options() const {
			return this->value->options;
		}

		float seam_angle() const {
			return this->value->seam_angle;
		}

		TParam val() const {
			return TParam(&this->value->val);
		}
	};

}
