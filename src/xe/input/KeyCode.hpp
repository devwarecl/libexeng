
#pragma once 

#ifndef __xe_input_keycode__
#define __xe_input_keycode__

#include <xe/Enum.hpp>

namespace xe { namespace input {
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
