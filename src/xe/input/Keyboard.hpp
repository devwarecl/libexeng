
#pragma once 

#ifndef __xe_input2_ikeyboard_hpp__
#define __xe_input2_ikeyboard_hpp__

#include <string>
#include <xe/input/Event.hpp>
#include <xe/input/InputDevice.hpp>
#include <xe/input/KeyboardStatus.hpp>
#include <xe/input/KeyStroke.hpp>

namespace xe { namespace input {

	/**
	 * @brief Interface to the keyboard device
	 */
	class EXENGAPI Keyboard : public InputDevice {
	public:
		virtual ~Keyboard() {}

		/**
		 * @brief Get the most recent key status
		 */
		virtual KeyboardStatus* getStatus() = 0;

		virtual const KeyboardStatus* getStatus() const = 0;

		/**
		 * @brief Get the key stroke event interface
		 */
		virtual Event<xe::input::KeyStroke>* getKeyStrokeEvent() = 0;
	};
}}

#endif 
