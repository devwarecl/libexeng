

#ifndef __EXENG_UI_CONTROL_HPP__
#define __EXENG_UI_CONTROL_HPP__

#include <exeng/Object.hpp>
#include <exeng/math/TSize.hpp>

namespace exeng { namespace ui {

    template<typename>
    class Container;
    
    class ControlPrivate;
    
    class EXENGAPI Control : public Object {
        friend class ControlPrivate;
    
    public:
        virtual TypeInfo getTypeInfo() const;
        
    public:
        Control();
        Control(ControlPrivate *privateCtrl);
        
        virtual ~Control();
        
        virtual Control* setParent(Control *control);
        virtual Control* getParent();
        virtual const Control* getParent() const;
        virtual const Container<Control>* getChilds() const;
        virtual Container<Control>* getChilds();
        
        virtual Control* setName(const std::string &name);
        virtual std::string getName() const;
        
        virtual Control* setText(const std::string &name);
        virtual std::string getText() const;
        
        virtual Control* setVisible(bool visible);
        virtual bool getVisible() const;
        
        virtual void* getHandle();
        virtual const void* getHandle() const;

		inline Control* setSize( int width, int height ) {
			return this->setSize(exeng::math::Size2i(width, height));
		}
		virtual Control* setSize( const exeng::math::Size2i &size);
		virtual exeng::math::Size2i getSize() const;


		inline Control* setPosition( int x, int y) {
			return this->setPosition(exeng::math::Vector2i(x, y));
		}
		virtual Control* setPosition( const exeng::math::Vector2i &pos);
		virtual exeng::math::Vector2i getPosition() const;

    protected:
        template<typename PrivateImpl>
        PrivateImpl* getImpl() {
            return static_cast<PrivateImpl*> (this->impl);
        }
    
        template<typename PrivateImpl>
        const PrivateImpl* getImpl() const {
            return static_cast<const PrivateImpl*> (this->impl);
        }
		
        ControlPrivate *impl;
    };
}}

#endif
