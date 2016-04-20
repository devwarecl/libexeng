
#pragma once

#ifndef __xe_input_inputmanagerimpl__
#define __xe_input_inputmanagerimpl__

#include <xe/input/InputManager.hpp>

namespace xe { namespace input {

	/**
	 * @brief InputManager base implementation
	 */
	class EXENGAPI InputManagerImpl : public InputManager {
	public:
		InputManagerImpl();

		virtual ~InputManagerImpl();

		virtual Keyboard* getKeyboard() override;

		virtual Mouse* getMouse() override;

		virtual void poll() override;

	protected:
		Keyboard *keyboard = nullptr;
		Mouse *mouse = nullptr;
	};
}}

#endif 
