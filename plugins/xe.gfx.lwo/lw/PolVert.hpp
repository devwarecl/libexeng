
#pragma once

#ifndef __lw_polvert_hpp__
#define __lw_polvert_hpp__

#include <xe/Vector.hpp>
#include "Wrapper.hpp"
#include "VMapPt.hpp"

namespace lw {
	
	class PolVert : public Wrapper<PolVert, ::lwPolVert> {
	public:
		PolVert();
		PolVert(::lwPolVert *value);

		int index() const;

		xe::Vector3f norm() const;

		int nvmaps() const;

		VMapPt vm(const int index) const;
	};
}

#endif
