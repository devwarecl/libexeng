
#include <exeng/ui/Window.hpp>
#include <exeng/ui/Label.hpp>
#include <exeng/ui/LabelPrivate.hpp>

namespace exeng { namespace ui {
	Label::Label(Window *parent, const std::string &text)  {
		this->setParent(parent)->setText(text);
	}


	TypeInfo Label::getTypeInfo() const {
		return TypeId<Window>();
	}
}}
