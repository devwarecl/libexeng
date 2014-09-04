


#include <exeng/ui/Control.hpp>
#include <exeng/ui/ControlPrivate.hpp>

#include <cassert>

namespace exeng { namespace ui {
    
    TypeInfo Control::getTypeInfo() const {
        return TypeId<Control>();
    }
    
    Control::Control() : impl(nullptr) {}
    
    Control::Control(ControlPrivate *privateCtrl) : impl(privateCtrl) {}
    
    Control::~Control() {
        if (this->impl) {
            delete this->impl;
            this->impl = nullptr;
        }
    }
    
    
    Control* Control::setParent(Control *control) {
        assert(this->impl != nullptr);
        
        this->impl->setParent(control);
        return this;
    }
    
    
    Control* Control::getParent() {
        assert(this->impl != nullptr);
        
        return this->impl->getParent();
    }
    
    
    const Control* Control::getParent() const {
        assert(this->impl != nullptr);
        
        return this->impl->getParent();
    }
    
    const Container<Control>* Control::getChilds() const {
        assert(this->impl != nullptr);
    
        return nullptr;
    }
    
    
    Container<Control>* Control::getChilds() {
        assert(this->impl != nullptr);
    
        return nullptr;
    }
    
    
    Control* Control::setName(const std::string &name) {
        assert(this->impl != nullptr);
        
        this->impl->setName(name);
    
        return this;
    }
    
    
    std::string Control::getName() const {
        assert(this->impl != nullptr);
    
        return this->impl->getName();
    }
    
    
    Control* Control::setText(const std::string &value) {
        assert(this->impl != nullptr);
    
        this->impl->setText(value);
    
        return this;
    }
    
    
    std::string Control::getText() const {
        assert(this->impl != nullptr);
    
        return this->impl->getText();
    }
    
    
    Control* Control::setVisible(bool visible) {
        assert(this->impl != nullptr);
    
        this->impl->setVisible(visible);
    
        return this;
    }
    

    bool Control::getVisible() const {
        assert(this->impl != nullptr);
    
        return this->impl->getVisible();
    }
    
    
    void* Control::getHandle() {
        assert(this->impl != nullptr);
        
        return this->impl->getHandle();
    }
    
    
    const void* Control::getHandle() const {
        assert(this->impl != nullptr);
    
        return this->impl->getHandle();
    }
    

	Control* Control::seSize( const exeng::Size2i &size) {
		assert(this->impl != nullptr);
		
		this->impl->seSize(size);
		return this;
	}
	

	exeng::Size2i Control::geSize() const {
		assert(this->impl != nullptr);

		return this->impl->geSize();
	}


	Control* Control::setPosition( const exeng::Vector2i &pos) {
		assert(this->impl != nullptr);

		this->impl->setPosition(pos);

		return this;
	}


	exeng::Vector2i Control::getPosition() const {
		assert(this->impl != nullptr);

		return this->impl->getPosition();
	}
}}
