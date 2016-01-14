
#include "Polygon.hpp"

namespace lw {
	Polygon::Polygon() {}
	Polygon::Polygon(::lwPolygon *value) : Wrapper<Polygon, ::lwPolygon>(value) {}

	int Polygon::flags() const {
		return this->value->flags;
	}

	xe::Vector3f Polygon::norm() const {
		return xe::Vector3f(&this->value->norm[0]);
	}
		
	int Polygon::nverts() const {
		return this->value->nverts;
	}

	int Polygon::part() const {
		return this->value->part;
	}

	int Polygon::smoothgrp() const {
		return this->value->smoothgrp;
	}

	Surface Polygon::surf() const {
		return Surface(this->value->surf);
	}

	int Polygon::type() const {
		return this->value->type;
	}

	PolVert Polygon::v(const int index) const {
		return PolVert(&this->value->v[index]);
	}
}
