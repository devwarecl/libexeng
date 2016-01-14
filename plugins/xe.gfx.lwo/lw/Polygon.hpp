
#pragma once

#include <xe/Vector.hpp>
#include "Wrapper.hpp"
#include "Surface.hpp"
#include "PolVert.hpp"

namespace lw {
	class Polygon : public Wrapper<Polygon, ::lwPolygon> {
	public:
		Polygon() {}
		Polygon(::lwPolygon *value) : Wrapper<Polygon, ::lwPolygon>(value) {}

		int flags() const {
			return this->value->flags;
		}

		xe::Vector3f norm() const {
			return xe::Vector3f(&this->value->norm[0]);
		}
		
		int nverts() const {
			return this->value->nverts;
		}

		int part() const {
			return this->value->part;
		}

		int smoothgrp() const {
			return this->value->smoothgrp;
		}

		Surface surf() const {
			return Surface(this->value->surf);
		}

		int type() const {
			return this->value->type;
		}

		PolVert v(const int index) const {
			return PolVert(&this->value->v[index]);
		}
	};
}
