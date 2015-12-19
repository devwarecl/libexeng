
#ifndef __EXENG_UI_LABEL_HPP__
#define __EXENG_UI_LABEL_HPP__

#include <exeng/ui/Control.hpp>

namespace xe { namespace ui {
	class LabelPrivate;
	class EXENGAPI Window;
	class EXENGAPI Label : public Control {
	public:
		Label(Window *parent=nullptr, const std::string &text="");

		virtual TypeInfo getTypeInfo() const;
	};
}}

#endif // __EXENG_UI_LABEL_HPP__
