
#pragma once

#ifndef __lw_polygon_hpp__
#define __lw_polygon_hpp__

#include <xe/Vector.hpp>
#include "Wrapper.hpp"
#include "Surface.hpp"
#include "PolVert.hpp"

namespace lw {
	class Polygon : public Wrapper<Polygon, ::lwPolygon> {
	public:
		Polygon();
		Polygon(::lwPolygon *value);

		int flags() const;

		xe::Vector3f norm() const;
		
		int nverts() const;

		int part() const;

		int smoothgrp() const;

		Surface surf() const;

		int type() const;

		PolVert v(const int index) const;
	};
}

#endif 
