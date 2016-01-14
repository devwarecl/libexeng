
#pragma once

#ifndef __lw_vparam_hpp__
#define __lw_vparam_hpp__

#include <xe/Vector.hpp>
#include "Wrapper.hpp"
#include "lwo/lwo2.h"

namespace lw {
	
	class VParam : public Wrapper<VParam, ::lwVParam> {
	public:
		VParam() {}
		VParam(::lwVParam *value) : Wrapper<VParam, ::lwVParam>(value) {}

		xe::Vector3f val() const {
			return xe::Vector3f(&this->value->val[0]);
		}

		int eindex() const {
			return this->value->eindex;
		}
	};
}

#endif
