
#include <xe/input/KeyboardStatus.hpp>

#include <cstring>

namespace xe { namespace input2 {
	KeyboardStatus::KeyboardStatus() {}

	void KeyboardStatus::setKeyStatus(KeyCode::Enum keyCode, KeyStatus::Enum keyStatus) {
		previous.status = current.status;
		current.status[keyCode] = keyStatus;
	}

	KeyStatus::Enum KeyboardStatus::getKeyStatus(KeyCode::Enum keyCode) const {
		return current.status[keyCode];
	}

	bool KeyboardStatus::isKeyPressed(KeyCode::Enum keyCode) const {
		return current.isPressed(keyCode);
	}

	bool KeyboardStatus::isKeyReleased(KeyCode::Enum keyCode) const {
		return current.isReleased(keyCode);
	}

	bool KeyboardStatus::isKeyPushed(KeyCode::Enum keyCode) const {
		return current.isPressed(keyCode) && previous.isReleased(keyCode);
	}

	bool KeyboardStatus::isKeyPopped(KeyCode::Enum keyCode) const {
		return current.isReleased(keyCode) && previous.isPressed(keyCode);
	}
}}
