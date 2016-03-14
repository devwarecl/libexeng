
#pragma once 

#ifndef __xe_input2_ikeyboard_hpp__
#define __xe_input2_ikeyboard_hpp__

#include <string>
#include <xe/input/IEvent.hpp>
#include <xe/input/IInputDevice.hpp>
#include <xe/input/KeyboardStatus.hpp>
#include <xe/input/KeyStroke.hpp>

namespace xe { namespace input2 {

	/**
	 * @brief Interface to the keyboard device
	 */
	class EXENGAPI IKeyboard : public IInputDevice {
	public:
		virtual ~IKeyboard() {}

		/**
		 * @brief Get the most recent key status
		 */
		virtual KeyboardStatus* getStatus() = 0;

		virtual const KeyboardStatus* getStatus() const = 0;

		/**
		 * @brief Get the key stroke event interface
		 */
		virtual IEvent<xe::input2::KeyStroke>* getKeyStrokeEvent() = 0;
	};
}}

#endif 
