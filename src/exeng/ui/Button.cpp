
#include <exeng/ui/Window.hpp>
#include <exeng/ui/Button.hpp>
#include <exeng/ui/ButtonPrivate.hpp>

namespace exeng { namespace ui {
	Button::Button(Window *parent, const std::string &text)  {
		this->setParent(parent)->setText(text);
	}


	TypeInfo Button::getTypeInfo() const {
		return TypeId<Window>();
	}
}}
