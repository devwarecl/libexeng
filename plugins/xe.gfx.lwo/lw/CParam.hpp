
#pragma once

#ifndef __lw_cparam_hpp__
#define __lw_cparam_hpp__

#include <xe/Vector.hpp>
#include "Wrapper.hpp"
#include "Texture.hpp"
#include "lwo/lwo2.h"

namespace lw {
	class CParam : public Wrapper<CParam, ::lwCParam> {
	public:
		CParam();
		CParam(::lwCParam *value);

		int eindex() const;

		xe::Vector3f rgb() const;

		Texture tex() const;
	};
}

#endif 
