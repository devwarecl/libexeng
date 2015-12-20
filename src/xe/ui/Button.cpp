
#include <xe/ui/Window.hpp>
#include <xe/ui/Button.hpp>
#include <xe/ui/ButtonPrivate.hpp>

namespace xe { namespace ui {
	Button::Button(Window *parent, const std::string &text)  {
		this->setParent(parent)->setText(text);
	}


	TypeInfo Button::getTypeInfo() const {
		return TypeId<Window>();
	}
}}
