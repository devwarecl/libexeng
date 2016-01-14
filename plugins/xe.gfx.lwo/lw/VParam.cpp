
#include "VParam.hpp"

namespace lw {
	VParam::VParam() {}
	VParam::VParam(::lwVParam *value) : Wrapper<VParam, ::lwVParam>(value) {}

	xe::Vector3f VParam::val() const {
		return xe::Vector3f(&this->value->val[0]);
	}

	int VParam::eindex() const {
		return this->value->eindex;
	}
}
