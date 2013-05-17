
#ifndef __EXENG_UI_WIDGET_HPP__
#define __EXENG_UI_WIDGET_HPP__

#include "../Object.hpp"
#include <string>
#include "../math/TSize.hpp"
#include "../math/TVector.hpp"

#include "../input/IEventRaiser.hpp"

namespace exeng {
    namespace ui {
        class Widget : public Object, public exeng::input::IEventRaiser {
        public:
            Widget();
            
            virtual ~Widget();
            
            void setName(const std::string &name);
            
            std::string getName() const;
            
            void setPosition(const exeng::math::Vector2i &pos);
            
            exeng::math::Vector2i getPosition() const;
            
            void setSize(const exeng::math::Size2i &size);
            
            exeng::math::Size2i getSize() const;
            
            virtual void pollEvents();
            
        private:
            struct Private;
            Private *impl;
        };
    }
}

#endif  //__EXENG_UI_WIDGET_HPP___
