
#ifndef __EXENG_UI_BUTTON_HPP__
#define __EXENG_UI_BUTTON_HPP__

#include <xe/ui/Control.hpp>

namespace xe { namespace ui {
	class LabelPrivate;
	class EXENGAPI Window;
	class EXENGAPI Button : public Control {
	public:
		Button(Window *parent=nullptr, const std::string &text="");

		virtual TypeInfo getTypeInfo() const;
	};
}}

#endif // __EXENG_UI_BUTTON_HPP__
