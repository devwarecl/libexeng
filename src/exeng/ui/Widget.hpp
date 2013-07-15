/**
 * @file Widget.hpp
 * @brief Widget abstract class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_UI_WIDGET_HPP__
#define __EXENG_UI_WIDGET_HPP__

#include <string>
#include <exeng/Object.hpp>
#include <exeng/math/TSize.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/input/IEventRaiser.hpp>

namespace exeng {
namespace ui {

/**
 * @brief The Widget class
 */
class Widget : public Object, public exeng::input::IEventRaiser {
public:
    Widget();
    
    virtual ~Widget();
    
    void setParent(const Widget *parent);
    const Widget* getParent() const;
    
    void setText(const std::string &name);
    std::string getText() const;
    
    void setPosition(const exeng::math::Vector2i &pos);
    exeng::math::Vector2i getPosition() const;
    
    void setSize(const exeng::math::Size2i &size);
    exeng::math::Size2i getSize() const;
    
    void addWidget(Widget *widget);
    void removeWidget(Widget *widget);
    int getWidgetCount() const;
    Widget* getWidget(int index) const;
    
    virtual void pollEvents();
    
private:
    struct Private;
    Private *impl;
};
}
}

#endif  //__EXENG_UI_WIDGET_HPP___
