
#include <xe/ui/Window.hpp>
#include <xe/ui/WindowPrivate.hpp>

#include <cassert>

namespace xe { namespace ui {
	Window::Window(Window *parent, const std::string &text) : Control(nullptr)  {
		this->setParent(parent)->setText(text);
	}


	bool Window::doEvent() {
		return this->getImpl<WindowPrivate>()->doEvent();
	}


	TypeInfo Window::getTypeInfo() const {
		return TypeId<Window>();
	}
}}
