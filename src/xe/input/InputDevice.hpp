
#pragma once 

#ifndef __xe_input_inputdevice__
#define __xe_input_inputdevice__

#include <xe/Config.hpp>

namespace xe { namespace input {
	class EXENGAPI InputDevice {
	public:
		virtual ~InputDevice() {}
		virtual void poll() = 0;
	};
}}

#endif 
