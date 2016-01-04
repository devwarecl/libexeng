#pragma once 

#include <xe/Enum.hpp>
#include <xe/Config.hpp>
#include <xe/Vector.hpp>
#include <xe/input2/IInputDevice.hpp>
#include <xe/input2/KeyStatus.hpp>

namespace xe { namespace input2 {

	struct MouseButton : public Enum {
		enum Enum {
			Unknown,
			ButtonLeft,
			ButtonRight,
			ButtonMiddle,
			Button1 = ButtonLeft,
			Button2 = ButtonRight,
			Button3 = ButtonMiddle,
			Button4 = ButtonMiddle,
			Button5 = ButtonMiddle,
			Button6 = ButtonMiddle,
			Button7 = ButtonMiddle,
			Button8 = ButtonMiddle,
			Total
		};
	};

	class MouseStatus {
	public:
		MouseStatus() {}

		Vector2i getPositionDelta() const {
			return current.position - previous.position;
		}

		Vector2i getPosition() const {
			return current.position;
		}

		void setPosition(const Vector2i &position) {
			previous.position = current.position;
			current.position = position;
		}

		KeyStatus::Enum getButtonStatus(MouseButton::Enum button) const {
			return current.status[button];
		}

		bool isButtonPressed(MouseButton::Enum button) const {
			return current.isPressed(button);
		}

		bool isButtonReleased(MouseButton::Enum button) const {
			return current.isReleased(button);
		}

		bool isButtonPushed(MouseButton::Enum button) const {
			return current.isPressed(button) && previous.isReleased(button);
		}

		bool isButtonPopped(MouseButton::Enum button) const {
			return current.isReleased(button) && previous.isPressed(button);
		}

	private:
		struct Status {
			Vector2i position;
			KeyStatus::Enum status[MouseButton::Total] = {};

			bool isPressed(MouseButton::Enum button) const {
				return status[button] == KeyStatus::Press;
			}

			bool isReleased(MouseButton::Enum button) const {
				return status[button] == KeyStatus::Release;
			}
		};

		Status current;
		Status previous;
	};

	class EXENGAPI IMouse : public IInputDevice {
	public:
		virtual ~IMouse() {}

		virtual MouseStatus getStatus() = 0;
	};
}}
