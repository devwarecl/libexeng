
#ifndef __EXENG_UI_WIN32_BUTTONPRIVATE_HPP__
#define __EXENG_UI_WIN32_BUTTONPRIVATE_HPP__

#include <exeng/ui/ControlPrivate.hpp>

namespace exeng { namespace ui { namespace win32 {
	class ButtonPrivate : public ControlPrivate {
	public:
		ButtonPrivate(void *parentHandle);
	};
}}}

#endif	//__EXENG_UI_BUTTONPRIVATE_HPP__
