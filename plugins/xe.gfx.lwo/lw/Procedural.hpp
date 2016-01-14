
#pragma once

#ifndef __lw_procedural_hpp__
#define __lw_procedural_hpp__

#include <string>
#include <xe/Vector.hpp>
#include "lwo/lwo2.h"

namespace lw {
	
	class Procedural : public Wrapper<Procedural, ::lwProcedural> {
	public:
		Procedural() {}
		Procedural(::lwProcedural *value) : Wrapper<Procedural, ::lwProcedural>(value) {}

		int axis() const {
			return this->value->axis;
		}

		void* data() const {
			return this->value->data;
		}

		std::string name() const {
			return this->value->name;
		}

		xe::Vector3f value_() const {
			return xe::Vector3f(&this->value->value[0]);
		}
	};	
}

#endif
