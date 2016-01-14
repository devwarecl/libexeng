
#pragma once

#ifndef __lw_axis_hpp__
#define __lw_axis_hpp__

#include <xe/Enum.hpp>

namespace lw {
	struct Axis : public xe::Enum {
		enum Enum {X, Y, Z};
	};
}

#endif 
