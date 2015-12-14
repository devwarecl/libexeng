
#ifndef __EXENG_UI_WIN32_WINDOWPRIVATE_HPP__
#define __EXENG_UI_WIN32_WINDOWPRIVATE_HPP__

#include <exeng/ui/win32/ControlPrivate.hpp>

namespace exeng { namespace ui { namespace win32 {
	class WindowPrivateWin32 : public ControlPrivateWin32 {
	public:
		WindowPrivateWin32();

		bool doEvent() const;
	};
}}}

#endif	//__EXENG_UI_WIN32_WINDOWPRIVATE_HPP__
