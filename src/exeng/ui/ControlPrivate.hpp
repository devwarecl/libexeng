
#ifndef __EXENG_UI_CONTROLPRIVATE_HPP__
#define __EXENG_UI_CONTROLPRIVATE_HPP__

#include <string>
#include <exeng/Config.hpp>
#include <exeng/Vector.hpp>
#include <exeng/Size.hpp>

namespace exeng { namespace ui {
    class Control;
    class EXENGAPI ControlPrivate {
    public:
        virtual ~ControlPrivate();
        
        virtual void* getHandle() = 0;
        virtual const void* getHandle() const = 0;

        virtual void setParent(Control *parent) = 0;
        virtual Control* getParent() const = 0;

        virtual void setText(const std::string &text) = 0;
        virtual std::string getText() const = 0;

        virtual void setName(const std::string &text) = 0;
        virtual std::string getName() const = 0;

        virtual void setVisible(bool visible) = 0;
        virtual bool getVisible() const = 0;

        virtual void seSize( const exeng::Size2i &size) = 0;
        virtual exeng::Size2i geSize() const = 0;

        virtual void setPosition( const exeng::Vector2i &pos) = 0;
        virtual exeng::Vector2i getPosition() const = 0;
        
    public:
        static ControlPrivate* new_();
    };
}}

#endif //__EXENG_UI_CONTROLPRIVATE_HPP__
