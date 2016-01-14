
#include "Point.hpp"

namespace lw {
	Point::Point() {}
	Point::Point(::lwPoint *value) : Wrapper<Point, ::lwPoint>(value) {}

	int Point::npols() const {
		return this->value->npols;
	}

	int Point::nvmaps() const {
		return this->value->nvmaps;
	}

	int Point::pol(const int index) const {
		return this->value->pol[index];
	}

	VMapPt Point::vm(const int index) const {
		return VMapPt(&this->value->vm[index]);
	}

	xe::Vector3f Point::pos() const {
		return xe::Vector3f(&this->value->pos[0]);
	}
}
