
#include <xe/Config.hpp>

#if defined(EXENG_WINDOWS)

#include <xe/ui/win32/WindowPrivate.hpp>

namespace xe { namespace ui { namespace win32 {

	WindowPrivateWin32::WindowPrivateWin32() {
		const char windowClassName[] = "WindowClassName";

		WNDCLASS wc = {0};
		wc.hInstance = ::GetModuleHandle(NULL);
		wc.lpfnWndProc = DefWindowProc;
		wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
		wc.lpszClassName = windowClassName;
		wc.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);

		if (! ::RegisterClass(&wc)) {
			throw WindowsException( ::GetLastError() );
		}

		HWND hWnd = ::CreateWindow(windowClassName, "", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, wc.hInstance, NULL);
		if (! hWnd) {
			throw WindowsException( ::GetLastError() );
		}

		this->hWnd = hWnd;
	}


	bool WindowPrivateWin32::doEvent() const {
		MSG msg = {0};
		BOOL result = ::GetMessage(&msg, this->hWnd, 0, 0);

		if (result == 0) {
			return false;
		}

		if (result == -1) {
			// throw exception
			return false;
		} else {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		return true;
	}
}}}

#endif
