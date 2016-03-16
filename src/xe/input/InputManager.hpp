
#pragma once

#ifndef __xe_input2_inputmanager_hpp__
#define __xe_input2_inputmanager_hpp__

#include <xe/input/IInputManager.hpp>

namespace xe { namespace input2 {

	/**
	 * @brief InputManager base implementation
	 */
	class EXENGAPI InputManager : public IInputManager {
	public:

		InputManager();

		virtual ~InputManager();

		virtual IKeyboard* getKeyboard() override;

		virtual IMouse* getMouse() override;

		virtual void poll() override;

	protected:
		IKeyboard *keyboard = nullptr;
		IMouse *mouse = nullptr;
	};
}}

#endif 
