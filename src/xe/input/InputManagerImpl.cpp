
#include "InputManagerImpl.hpp"

namespace xe { namespace input {

	InputManagerImpl::InputManagerImpl() {}

	InputManagerImpl::~InputManagerImpl() {}
	
	Keyboard* InputManagerImpl::getKeyboard() {
		return this->keyboard;
	}

	Mouse* InputManagerImpl::getMouse() {
		return this->mouse;
	}

	void InputManagerImpl::poll() {
		InputDevice* devices[] = {keyboard, mouse};

		for (InputDevice* device : devices) {
			if (device) {
				device->poll();
			}
		}
	}
}}
