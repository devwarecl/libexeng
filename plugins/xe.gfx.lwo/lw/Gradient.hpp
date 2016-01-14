
#pragma once

#ifndef __lw_gradient_hpp__
#define __lw_gradient_hpp__

#include <string>
#include "Wrapper.hpp"
#include "GradKey.hpp"
#include "lwo/lwo2.h"

namespace lw {
	class Gradient : public Wrapper<Gradient, ::lwGradient> {
	public:
		Gradient();
		Gradient(::lwGradient *value);

		float end() const;

		short ikey(const int index) const;

		std::string itemname() const;

		GradKey key(const int index) const;

		std::string paramname() const;

		int repeat() const;

		float start() const;
	};
}

#endif
