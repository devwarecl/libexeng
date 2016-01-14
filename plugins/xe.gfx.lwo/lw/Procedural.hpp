
#pragma once

#ifndef __lw_procedural_hpp__
#define __lw_procedural_hpp__

#include <string>
#include <xe/Vector.hpp>
#include "Wrapper.hpp"
#include "lwo/lwo2.h"

namespace lw {	
	class Procedural : public Wrapper<Procedural, ::lwProcedural> {
	public:
		Procedural();
		Procedural(::lwProcedural *value);

		int axis() const;

		void* data() const;

		std::string name() const;

		xe::Vector3f value_() const;
	};	
}

#endif
