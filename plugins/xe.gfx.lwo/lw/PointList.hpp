
#pragma once

#ifndef __lw_pointlist_hpp__
#define __lw_pointlist_hpp__

#include "Array.hpp"
#include "Wrapper.hpp"
#include "Point.hpp"

namespace lw {
	class PointList : public Wrapper<PointList, ::lwPointList>, public Array<Point> {
	public:
		PointList();
		PointList(::lwPointList *value);

		int count() const;

		int offset() const;

		Point pt(const int index) const;
	};
}

#endif
