

#include <xe/ui/Control.hpp>

#if defined(EXENG_WINDOWS)

#include <xe/ui/win32/ControlPrivate.hpp>

namespace xe { namespace ui { namespace win32 {
    
	ControlPrivateWin32::ControlPrivateWin32() {
		this->hInstance = ::GetModuleHandle(NULL);
		this->hWnd = NULL;
		this->parent = nullptr;
		this->visible = false;
	}


	ControlPrivateWin32::~ControlPrivateWin32() {
		if (this->hWnd) {
			::CloseWindow(this->hWnd);
			::DestroyWindow(this->hWnd);

			this->hWnd = NULL;
		}
	}


	void* ControlPrivateWin32::getHandle() {
		return this->hWnd;
	}


	const void* ControlPrivateWin32::getHandle() const {
		return this->hWnd;
	}


	void ControlPrivateWin32::setParent(Control *parent) {
		if (this->parent == parent) {
			return;
		}

		HWND hWnd;

		if (parent != nullptr) {
			// HACK: Resolve soon plz
			hWnd = static_cast<HWND>(parent->getHandle());
		} else {
			hWnd = NULL;
		}

		if (! ::SetParent(this->hWnd, hWnd)) {
			throw WindowsException( ::GetLastError() );
		} 
	
		this->parent = parent;
	}


	Control* ControlPrivateWin32::getParent() const {
		return this->parent;
	}



	void ControlPrivateWin32::setText(const std::string &text) {
		if (! ::SetWindowText(this->hWnd, text.c_str())) {
			throw WindowsException( ::GetLastError() );
		}

		this->text = text;
	}


	std::string ControlPrivateWin32::getText() const {
		return this->text;
	}


	void ControlPrivateWin32::setName(const std::string &name) {
		this->name = name;
	}


	std::string ControlPrivateWin32::getName() const {
		return this->name;
	}


	void ControlPrivateWin32::setVisible(bool visible) {
		if (this->visible == visible) {
			return;
		}

		::ShowWindow(this->hWnd, visible?SW_SHOW:SW_HIDE);
		this->visible = visible;
	}


	bool ControlPrivateWin32::getVisible() const {
		bool status = ::IsWindowVisible(this->hWnd)?true:false;
		this->visible = status;

		return status;
	}


	void ControlPrivateWin32::seSize( const xe::Size2i &size) {
		if (! ::SetWindowPos(this->hWnd, HWND_NOTOPMOST, 0, 0, size.width, size.height, SWP_NOMOVE)) {
			throw WindowsException( ::GetLastError() );
		}
	}


	xe::Size2i ControlPrivateWin32::geSize() const {
		RECT rect = {0};

		if (! ::GetClientRect(this->hWnd, &rect)) {
			throw WindowsException( ::GetLastError() );
		}

		return xe::Size2i(rect.right-rect.left, rect.bottom-rect.top);
	}


	void ControlPrivateWin32::setPosition( const xe::Vector2i &pos) {
		if (this->getParent() == nullptr) {
			if (! ::SetWindowPos(this->hWnd, HWND_NOTOPMOST, pos.x, pos.y, 0, 0, SWP_NOSIZE)) {
				throw WindowsException( ::GetLastError() );
			}
		} else {

		}
	}


	xe::Vector2i ControlPrivateWin32::getPosition() const {
		RECT rc = {0};

		if (! ::GetClientRect(this->hWnd, &rc) ) {
			throw WindowsException( ::GetLastError() );
		}

		return xe::Vector2i(rc.left, rc.top);
	}
}}}

#endif 
