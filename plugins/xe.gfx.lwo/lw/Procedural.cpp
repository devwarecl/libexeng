
#include "Procedural.hpp"

namespace lw {
	Procedural::Procedural() {}
	Procedural::Procedural(::lwProcedural *value) : Wrapper<Procedural, ::lwProcedural>(value) {}

	int Procedural::axis() const {
		return this->value->axis;
	}

	void* Procedural::data() const {
		return this->value->data;
	}

	std::string Procedural::name() const {
		return this->value->name;
	}

	xe::Vector3f Procedural::value_() const {
		return xe::Vector3f(&this->value->value[0]);
	}
}
