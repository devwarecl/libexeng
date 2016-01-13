
#pragma once

namespace lw {
	
	class EParam : public Wrapper<EParam, ::lwEParam> {
	public:
		EParam() {}
		EParam(::lwEParam *value) : Wrapper<EParam, ::lwEParam>(value) {}

		int eindex() const {
			return this->value->eindex;
		}

		float val() const {
			return this->value->val;
		}
	};

}
