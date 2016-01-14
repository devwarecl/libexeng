
#pragma once

#ifndef __lw_point_hpp__
#define __lw_point_hpp__

#include <xe/Vector.hpp>
#include "Wrapper.hpp"
#include "VMapPt.hpp"

namespace lw {	
	class Point : public Wrapper<Point, ::lwPoint> {
	public:
		Point();
		Point(::lwPoint *value);

		int npols() const;

		int nvmaps() const;

		int pol(const int index) const;

		VMapPt vm(const int index) const;

		xe::Vector3f pos() const;
	};
}

#endif
