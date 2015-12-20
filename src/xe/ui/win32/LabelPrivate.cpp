
#include <xe/Config.hpp>

#if defined(EXENG_WINDOWS)

#include <xe/ui/win32/LabelPrivate.hpp>

namespace xe { namespace ui { namespace win32 {
	LabelPrivateWin32::LabelPrivateWin32(void *parentHandle) {
		HWND hWnd = ::CreateWindow(
					   "Static",
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
