
#ifndef __EXENG_UI_WIN32_WINDOWPRIVATE_HPP__
#define __EXENG_UI_WIN32_WINDOWPRIVATE_HPP__

#include <exeng/ui/win32/ControlPrivate.hpp>

namespace exeng { namespace ui { namespace win32 {
	class WindowPrivate : public ControlPrivate {
	public:
		WindowPrivate();

		bool doEvent() const;
	};
}}}

#endif	//__EXENG_UI_WIN32_WINDOWPRIVATE_HPP__
