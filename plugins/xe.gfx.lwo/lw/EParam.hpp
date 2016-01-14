
#pragma once

#ifndef __lw_eparam_hpp__
#define __lw_eparam_hpp__

#include "Wrapper.hpp"
#include "lwo/lwo2.h"

namespace lw {
	
	class EParam : public Wrapper<EParam, ::lwEParam> {
	public:
		EParam();
		EParam(::lwEParam *value);

		int eindex() const;

		float val() const;
	};
}

#endif