
#ifndef __EXENG_UI_WINDOW_HPP__
#define __EXENG_UI_WINDOW_HPP__

#include <exeng/ui/Control.hpp>

namespace xe { namespace ui {
	class WindowPrivate;
	class EXENGAPI Window : public Control {
	public:
		Window(Window *parent=nullptr, const std::string &text="");

		virtual TypeInfo getTypeInfo() const;

		// HACK: temporary method (to make the window work)
		virtual bool doEvent();
	};
}}

#endif	//__EXENG_UI_WINDOW_HPP__
