
#pragma once

#ifndef __lw_gradkey_hpp__
#define __lw_gradkey_hpp__

#include "Wrapper.hpp"
#include "lwo/lwo2.h"

namespace lw {	
	class GradKey : public Wrapper<GradKey, ::lwGradKey> {
	public:
		GradKey();
		GradKey(::lwGradKey *value);
	};
}

#endif
