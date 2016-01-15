
#include "PolygonList.hpp"

namespace lw {
	PolygonList::PolygonList() {}

	PolygonList::PolygonList(::lwPolygonList *value) : 
		Wrapper<PolygonList, ::lwPolygonList>(value), 
		Array<Polygon, ::lwPolygon>(value->pol, value->count) 
	{}
		
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

	Array<Polygon, ::lwPolygon> PolygonList::polygons() const {
		return Array<Polygon, ::lwPolygon>(this->value->pol, this->value->count);
	}
}
