
#pragma once

namespace lw {

	
	class PolygonList : public Wrapper<PolygonList, ::lwPolygonList> {
	public:
		PolygonList() {}
		PolygonList(::lwPolygonList *value) : Wrapper<PolygonList, ::lwPolygonList>(value) {}
		
		int count() const {
			return this->value->count;
		}

		Polygon pol(const int index) const {
			return Polygon(&this->value->pol[index]);
		}

		int vcount() const {
			return this->value->vcount;
		}

		int offset() const {
			return this->value->offset;
		}

		int voffset() const {
			return this->value->voffset;
		}
	};

}
