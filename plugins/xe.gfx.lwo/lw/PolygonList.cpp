
#include "PolygonList.hpp"

namespace lw {
	PolygonList::PolygonList() {}
	PolygonList::PolygonList(::lwPolygonList *value) : Wrapper<PolygonList, ::lwPolygonList>(value) {}
		
	int PolygonList::count() const {
		return this->value->count;
	}

	Polygon PolygonList::pol(const int index) const {
		return Polygon(&this->value->pol[index]);
	}

	int PolygonList::vcount() const {
		return this->value->vcount;
	}

	int PolygonList::offset() const {
		return this->value->offset;
	}

	int PolygonList::voffset() const {
		return this->value->voffset;
	}
}
