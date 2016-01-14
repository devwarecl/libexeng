
#pragma once

#ifndef __lw_polygonlist_hpp__
#define __lw_polygonlist_hpp__

#include "Wrapper.hpp"
#include "Polygon.hpp"

namespace lw {
	class PolygonList : public Wrapper<PolygonList, ::lwPolygonList> {
	public:
		PolygonList();
		PolygonList(::lwPolygonList *value);
		
		int count() const;

		Polygon pol(const int index) const;

		int vcount() const;

		int offset() const;

		int voffset() const;
	};
}

#endif 
