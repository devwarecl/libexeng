

#if defined(EXENG_WINDOWS)

#include <exeng/ui/Control.hpp>
#include <exeng/ui/Win32ControlPrivate.hpp>

namespace exeng { namespace ui { namespace win32 {
    
	Win32ControlPrivate::Win32ControlPrivate() {
		this->hInstance = ::GetModuleHandle(NULL);
		this->hWnd = NULL;
		this->parent = nullptr;
		this->visible = false;
	}


	Win32ControlPrivate::~Win32ControlPrivate() {
		if (this->hWnd) {
			::CloseWindow(this->hWnd);
			::DestroyWindow(this->hWnd);

			this->hWnd = NULL;
		}
	}


	void* Win32ControlPrivate::getHandle() {
		return this->hWnd;
	}


	const void* Win32ControlPrivate::getHandle() const {
		return this->hWnd;
	}


	void Win32ControlPrivate::setParent(Control *parent) {
		if (this->parent == parent) {
			return;
		}

		HWND hWnd;

		if (parent != nullptr) {
			hWnd = parent->impl->hWnd;
		} else {
			hWnd = NULL;
		}

		if (! ::SetParent(this->hWnd, hWnd)) {
			throw WindowsException( ::GetLastError() );
		} 
	
		this->parent = parent;
	}


	Control* Win32ControlPrivate::getParent() const {
		return this->parent;
	}



	void Win32ControlPrivate::setText(const std::string &text) {
		if (! ::SetWindowText(this->hWnd, text.c_str())) {
			throw WindowsException( ::GetLastError() );
		}

		this->text = text;
	}


	std::string Win32ControlPrivate::getText() const {
		return this->text;
	}


	void Win32ControlPrivate::setName(const std::string &name) {
		this->name = name;
	}


	std::string Win32ControlPrivate::getName() const {
		return this->name;
	}


	void Win32ControlPrivate::setVisible(bool visible) {
		if (this->visible == visible) {
			return;
		}

		::ShowWindow(this->hWnd, visible?SW_SHOW:SW_HIDE);
		this->visible = visible;
	}


	bool Win32ControlPrivate::getVisible() const {
		bool status = ::IsWindowVisible(this->hWnd)?true:false;
		this->visible = status;

		return status;
	}


	void Win32ControlPrivate::setSize( const exeng::math::Size2i &size) {
		if (! ::SetWindowPos(this->hWnd, HWND_NOTOPMOST, 0, 0, size.width, size.height, SWP_NOMOVE)) {
			throw WindowsException( ::GetLastError() );
		}
	}


	exeng::math::Size2i Win32ControlPrivate::getSize() const {
		RECT rect = {0};

		if (! ::GetClientRect(this->hWnd, &rect)) {
			throw WindowsException( ::GetLastError() );
		}

		return exeng::math::Size2i(rect.right-rect.left, rect.bottom-rect.top);
	}


	void Win32ControlPrivate::setPosition( const exeng::math::Vector2i &pos) {
		if (this->getParent() == nullptr) {
			if (! ::SetWindowPos(this->hWnd, HWND_NOTOPMOST, pos.x, pos.y, 0, 0, SWP_NOSIZE)) {
				throw WindowsException( ::GetLastError() );
			}
		} else {

		}
	}


	exeng::math::Vector2i Win32ControlPrivate::getPosition() const {
		RECT rc = {0};

		if (! ::GetClientRect(this->hWnd, &rc) ) {
			throw WindowsException( ::GetLastError() );
		}

		return exeng::math::Vector2i(rc.left, rc.top);
	}
}}}

#endif 
