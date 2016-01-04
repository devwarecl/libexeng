
#pragma once 

#ifndef __xe_input2_iinputdevice_hpp__
#define __xe_input2_iinputdevice_hpp__

namespace xe { namespace input2 {
	class IInputDevice {
	public:
		virtual ~IInputDevice() {}
		virtual void poll() = 0;
	};
}}

#endif 
