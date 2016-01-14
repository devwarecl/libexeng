
#include "TParam.hpp"
#include "Texture.hpp"

namespace lw {
	TParam::TParam() {}
	TParam::TParam(::lwTParam *value) : Wrapper<TParam, ::lwTParam>(value) {}

	float TParam::val() const {
		return this->value->val;
	}

	int TParam::eindex() const {
		return this->value->eindex;
	}

	Texture TParam::tex() const {
		return Texture(this->value->tex);
	}
}
