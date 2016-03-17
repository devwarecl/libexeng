
#pragma once 

#ifndef __xe_input2_keycode_hpp__
#define __xe_input2_keycode_hpp__

#include <xe/Enum.hpp>
#include <ostream>

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
		
		friend std::ostream& operator<< (std::ostream& os, Enum keyCode) {
            switch (keyCode) {
                case Unknown:   os << "Unknown"; break;
                case KeyEsc:    os << "KeyEsc"; break;
                case KeyEnter:  os << "KeyEnter"; break;
                case KeyUp:     os << "KeyUp"; break;
                case KeyDown:   os << "KeyDown"; break;
                case KeyLeft:   os << "KeyLeft"; break;
                case KeyRight:  os << "KeyRight"; break;
            }
            
            return os;
		}
	};
}}

#endif
