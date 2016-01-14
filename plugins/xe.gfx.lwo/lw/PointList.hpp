
#pragma once

#ifndef __lw_pointlist_hpp__
#define __lw_pointlist_hpp__

#include "Wrapper.hpp"
#include "Point.hpp"

namespace lw {
	
	class PointList : public Wrapper<PointList, ::lwPointList> {
	public:
		PointList() {}
		PointList(::lwPointList *value) : Wrapper<PointList, ::lwPointList>(value) {}

		int count() const {
			return this->value->count;
		}

		int offset() const {
			return this->value->offset;
		}

		Point pt(const int index) const {
			return Point(&this->value->pt[index]);
		}
	};
}

#endif
