
#include "PointList.hpp"

namespace lw {
	PointList::PointList() {}
	PointList::PointList(::lwPointList *value) : Wrapper<PointList, ::lwPointList>(value) {}

	int PointList::count() const {
		return this->value->count;
	}

	int PointList::offset() const {
		return this->value->offset;
	}

	Point PointList::pt(const int index) const {
		return Point(&this->value->pt[index]);
	}
}
