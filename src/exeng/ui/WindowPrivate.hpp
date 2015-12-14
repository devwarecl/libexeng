
#ifndef __EXENG_UI_WINDOWPRIVATE_HPP__
#define __EXENG_UI_WINDOWPRIVATE_HPP__

#include <exeng/ui/ControlPrivate.hpp>

namespace exeng { namespace ui { 
    class EXENGAPI WindowPrivate : public ControlPrivate {
    public:
        virtual ~WindowPrivate();

        virtual bool doEvent() const = 0;
    };
}}

#endif  //__EXENG_UI_WIN32_WINDOWPRIVATE_HPP__
