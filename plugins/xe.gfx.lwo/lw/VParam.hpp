
#pragma once

#ifndef __lw_vparam_hpp__
#define __lw_vparam_hpp__

#include <xe/Vector.hpp>
#include "Wrapper.hpp"
#include "lwo/lwo2.h"

namespace lw {
	
	class VParam : public Wrapper<VParam, ::lwVParam> {
	public:
		VParam();
		VParam(::lwVParam *value);

		xe::Vector3f val() const;

		int eindex() const;
	};
}

#endif
