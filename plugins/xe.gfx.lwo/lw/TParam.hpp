
#pragma once

namespace lw {
	class TParam : public Wrapper<TParam, ::lwTParam> {
	public:
		TParam() {}
		TParam(::lwTParam *value) : Wrapper<TParam, ::lwTParam>(value) {}

		float val() const {
			return this->value->val;
		}

		int eindex() const {
			return this->value->eindex;
		}

		Texture tex() const;
	};
}
