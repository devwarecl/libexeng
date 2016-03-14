
#pragma once 

#ifndef __xe_input2_keycode_hpp__
#define __xe_input2_keycode_hpp__

#include <xe/Enum.hpp>

namespace xe { namespace input2 {
	struct KeyCode : public Enum {
		enum Enum {
			Unknown,
			KeyEsc,
			KeyEnter,
			KeyUp,
			KeyDown,
			KeyLeft,
			KeyRight,
			Total
		};
	};
}}

#endif
