
#pragma once

#include "Wrapper.hpp"
#include "lwo/lwo2.h"

namespace lw {
	
	class GradKey : public Wrapper<GradKey, ::lwGradKey> {
	public:
		GradKey() {}
		GradKey(::lwGradKey *value) : Wrapper<GradKey, ::lwGradKey>(value) {}

	};

}
