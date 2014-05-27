
#include <exeng/Config.hpp>

#if defined(EXENG_WINDOWS)

#include <exeng/ui/win32/ButtonPrivate.hpp>

namespace exeng { namespace ui { namespace win32 {

	ButtonPrivateWin32::ButtonPrivateWin32(void *parentHandle) {
		HWND hWnd = ::CreateWindow(
					   "Button",
					   NULL,
					   WS_CHILD,
					   10, 10, 124, 25,
					   static_cast<HWND>(parentHandle),
					   NULL,
					   ::GetModuleHandle(NULL),
					   NULL);

		if (! hWnd) {
			throw WindowsException( ::GetLastError() );
		}

		this->hWnd = hWnd;
	}
}}}

#endif