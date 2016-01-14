
#pragma once

#include <string>
#include "Wrapper.hpp"
#include "GradKey.hpp"
#include "lwo/lwo2.h"

namespace lw {
	
	class Gradient : public Wrapper<Gradient, ::lwGradient> {
	public:
		Gradient() {}
		Gradient(::lwGradient *value) : Wrapper<Gradient, ::lwGradient>(value) {}

		float end() const {
			return this->value->end;
		}

		short ikey(const int index) const {
			return this->value->ikey[index];
		}

		std::string itemname() const {
			return this->value->itemname;
		}

		GradKey key(const int index) const {
			return GradKey(&this->value->key[index]);
		}

		std::string paramname() const {
			return this->value->paramname;
		}

		int repeat() const {
			return this->value->repeat;
		}

		float start() const {
			return this->value->start;
		}

	};
}
