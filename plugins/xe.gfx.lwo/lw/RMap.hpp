
#pragma once

#ifndef __lw_rmap_hpp__
#define __lw_rmap_hpp__

#include "Wrapper.hpp"
#include "TParam.hpp"
#include "lwo/lwo2.h"

namespace lw {
	class RMap : public Wrapper<RMap, ::lwRMap> {
	public:
		RMap();
		RMap(::lwRMap *value);

		int cindex() const;

		int options() const;

		float seam_angle() const;

		TParam val() const;
	};
}

#endif
