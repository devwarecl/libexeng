
#include "CParam.hpp"

namespace lw {
	CParam::CParam() {}
	CParam::CParam(::lwCParam *value) : Wrapper<CParam, ::lwCParam>(value) {}

	int CParam::eindex() const {
		return this->value->eindex;
	}

	xe::Vector3f CParam::rgb() const {
		return xe::Vector3f(&this->value->rgb[0]);
	}

	Texture CParam::tex() const {
		return Texture(this->value->tex);
	}
}
