
#include <xe/ui/Window.hpp>
#include <xe/ui/Label.hpp>
#include <xe/ui/LabelPrivate.hpp>

namespace xe { namespace ui {
	Label::Label(Window *parent, const std::string &text)  {
		this->setParent(parent)->setText(text);
	}


	TypeInfo Label::getTypeInfo() const {
		return TypeId<Window>();
	}
}}
