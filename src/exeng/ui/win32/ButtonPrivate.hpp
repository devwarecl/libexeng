
#ifndef __EXENG_UI_WIN32_BUTTONPRIVATE_HPP__
#define __EXENG_UI_WIN32_BUTTONPRIVATE_HPP__

#include <exeng/ui/win32/ControlPrivate.hpp>

namespace exeng { namespace ui { namespace win32 {
	class ButtonPrivateWin32 : public ControlPrivateWin32 {
	public:
		ButtonPrivateWin32(void *parentHandle);
	};
}}}

#endif	//__EXENG_UI_BUTTONPRIVATE_HPP__
