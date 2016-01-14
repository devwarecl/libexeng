
#pragma once

#ifndef __lw_tparam_hpp__
#define __lw_tparam_hpp__

#include "Wrapper.hpp"
#include "lwo/lwo2.h"

namespace lw {
	class Texture;
	class TParam : public Wrapper<TParam, ::lwTParam> {
	public:
		TParam();
		TParam(::lwTParam *value);

		float val() const;

		int eindex() const;

		Texture tex() const;
	};
}

#endif
