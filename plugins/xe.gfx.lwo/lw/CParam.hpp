
#pragma once

namespace lw {
	class CParam : public Wrapper<CParam, ::lwCParam> {
	public:
		CParam() {}
		CParam(::lwCParam *value) : Wrapper<CParam, ::lwCParam>(value) {}

		int eindex() const {
			return this->value->eindex;
		}

		xe::Vector3f rgb() const {
			return xe::Vector3f(&this->value->rgb[0]);
		}

		Texture tex() const {
			return Texture(this->value->tex);
		}
	};
}
