
#ifndef __EXENG_UI_WIN32_CONTROLPRIVATE_HPP__
#define __EXENG_UI_WIN32_CONTROLPRIVATE_HPP__

#include <exeng/ui/ControlPrivate.hpp>

#if defined(EXENG_WINDOWS)

#include <Windows.h>
#include <stdexcept>

namespace exeng { namespace ui { namespace win32 {
	class WindowsException : public std::runtime_error {
	public:
		WindowsException(DWORD errorCode) : runtime_error("") {
			const int bufferSize = 256;
			char buffer[bufferSize] = {0};

			::FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM, 
				NULL, errorCode, 
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
				buffer,  bufferSize, NULL
			);

			this->msg = std::string(buffer);
			this->errorCode = errorCode;
		}
	
		DWORD getErrorCode() const {
			return this->errorCode;
		}
	
		virtual const char* what() const {
			return msg.c_str();
		}
	
	private:
		DWORD errorCode;
		std::string msg;
	};
    
    
	class Control;
	class ControlPrivate : public exeng::ui::ControlPrivate {
	public:
		ControlPrivate();
		virtual ~ControlPrivate();
	
		virtual void* getHandle();
		virtual const void* getHandle() const;

		virtual void setParent(Control *parent);
		virtual Control* getParent() const;

		virtual void setText(const std::string &text);
		virtual std::string getText() const;

		virtual void setName(const std::string &text);
		virtual std::string getName() const;

		virtual void setVisible(bool visible);
		virtual bool getVisible() const;

		virtual void setSize( const exeng::math::Size2i &size);
		virtual exeng::math::Size2i getSize() const;

		virtual void setPosition( const exeng::math::Vector2i &pos);
		virtual exeng::math::Vector2i getPosition() const;
        
	public:
		HINSTANCE hInstance;
		HWND hWnd;
        
	private:
		Control *parent;
		std::string text;
		std::string name;
		mutable bool visible;
	};
}}}

#endif  // defined(EXENG_WINDOWS)	

#endif //__EXENG_UI_WIN32_WIN32CONTROLPRIVATE_HPP__
