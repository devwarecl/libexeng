
#include "RMap.hpp"

namespace lw {
	RMap::RMap() {}
	RMap::RMap(::lwRMap *value) : Wrapper<RMap, ::lwRMap>(value) {}

	int RMap::cindex() const {
		return this->value->cindex;
	}

	int RMap::options() const {
		return this->value->options;
	}

	float RMap::seam_angle() const {
		return this->value->seam_angle;
	}

	TParam RMap::val() const {
		return TParam(&this->value->val);
	}
}
