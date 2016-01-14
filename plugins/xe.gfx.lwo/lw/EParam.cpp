
#include "EParam.hpp"

namespace lw {
	EParam::EParam() {}
	EParam::EParam(::lwEParam *value) : Wrapper<EParam, ::lwEParam>(value) {}

	int EParam::eindex() const {
		return this->value->eindex;
	}

	float EParam::val() const {
		return this->value->val;
	}
}
