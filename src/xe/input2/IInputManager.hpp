
#pragma once 

#ifndef __xe_input2_iinputmanager_hpp__
#define __xe_input2_iinputmanager_hpp__

#include <xe/Config.hpp>
#include <xe/input2/IKeyboard.hpp>
#include <xe/input2/IMouse.hpp>

namespace xe { namespace input2 {
	class EXENGAPI IInputManager {
	public:
		virtual ~IInputManager() {}

		/**
		 * @brief Get the current keyboard interface
		 */
		virtual IKeyboard* getKeyboard() = 0;

		/**
		 * @brief Get the current mouse interface
		 */
		virtual IMouse* getMouse() = 0;

		/**
		 * Poll all available devices
		 */
		virtual void poll() = 0;
	};
}}

#endif 
