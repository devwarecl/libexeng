
#include "Gradient.hpp"

namespace lw {

	Gradient::Gradient() {}
	Gradient::Gradient(::lwGradient *value) : Wrapper<Gradient, ::lwGradient>(value) {}

	float Gradient::end() const {
		return this->value->end;
	}

	short Gradient::ikey(const int index) const {
		return this->value->ikey[index];
	}

	std::string Gradient::itemname() const {
		return this->value->itemname;
	}

	GradKey Gradient::key(const int index) const {
		return GradKey(&this->value->key[index]);
	}

	std::string Gradient::paramname() const {
		return this->value->paramname;
	}

	int Gradient::repeat() const {
		return this->value->repeat;
	}

	float Gradient::start() const {
		return this->value->start;
	}
}
