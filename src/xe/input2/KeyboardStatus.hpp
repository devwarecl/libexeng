
#pragma once 

#ifndef __xe_input2_keyboardstatus_hpp__
#define __xe_input2_keyboardstatus_hpp__

#include <array>
#include <xe/Config.hpp>
#include <xe/input2/KeyStatus.hpp>
#include <xe/input2/KeyCode.hpp>

namespace xe { namespace input2 {
	class EXENGAPI KeyboardStatus {
	public:
		KeyboardStatus();

		void setKeyStatus(KeyCode::Enum keyCode, KeyStatus::Enum keyStatus);

		KeyStatus::Enum getKeyStatus(KeyCode::Enum keyCode) const;

		bool isKeyPressed(KeyCode::Enum keyCode) const;
		bool isKeyReleased(KeyCode::Enum keyCode) const;
		bool isKeyPushed(KeyCode::Enum keyCode) const;
		bool isKeyPopped(KeyCode::Enum keyCode) const;
	private:
		static const int KEY_COUNT = KeyCode::Total + 1;

		struct EXENGAPI Status {
			std::array<KeyStatus::Enum, KEY_COUNT> status;

			Status() {
				std::generate(std::begin(status), std::end(status), []() {
					return KeyStatus::Release;
				});
			}

			bool isPressed(KeyCode::Enum key) const {
				return status[key] == KeyStatus::Press;
			}

			bool isReleased(KeyCode::Enum key) const {
				return status[key] == KeyStatus::Release;
			}
		};

		Status current;
		Status previous;
	};
}}

#endif 
