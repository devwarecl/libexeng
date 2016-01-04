
#include <xe/input2/InputManager.hpp>

namespace xe { namespace input2 {

	InputManager::InputManager() {}

	InputManager::~InputManager() {}
	
	IKeyboard* InputManager::getKeyboard() {
		return this->keyboard;
	}

	IMouse* InputManager::getMouse() {
		return this->mouse;
	}

	void InputManager::poll() {
		IInputDevice* devices[] = {
			this->keyboard,
			this->mouse
		};

		for (IInputDevice* device : devices) {
			if (device) {
				device->poll();
			}
		}
	}
}}
