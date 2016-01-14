
#include "PolVert.hpp"

namespace lw {
	PolVert::PolVert() {}
	PolVert::PolVert(::lwPolVert *value) : Wrapper<PolVert, ::lwPolVert>(value) {}

	int PolVert::index() const {
		return this->value->index;
	}

	xe::Vector3f PolVert::norm() const {
		return xe::Vector3f(&this->value->norm[0]);
	}

	int PolVert::nvmaps() const {
		return this->value->nvmaps;
	}

	VMapPt PolVert::vm(const int index) const {
		return VMapPt(&this->value->vm[index]);
	}
}
