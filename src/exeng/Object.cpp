/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <cassert>
#include <typeinfo>
#include <sstream>
#include <stdexcept>
#include <exeng/Object.hpp>
// #include <iostream>

namespace xe {
#if defined (EXENG_DEBUG)
	int count = 0;
#endif

	Object::Object() {
#if defined (EXENG_DEBUG)
		++count;
		// std::cout << "Creating object (currentCount: " << count << ")" << std::endl;
#endif
	}


	Object::~Object() {
#if defined (EXENG_DEBUG)
		// std::cout << "Destroying object (currentCount: " << count << ")(type: " << this->toString() << ")" << std::endl;
		--count;
#endif
	}


	std::string	Object::toString() const {
		// By default, convert the direction address to a string
		std::stringstream ss;
    
		ss << "Object " << this->getTypeInfo().getStdTypeInfo().name() << " at " << (int*)this;

		return ss.str();
	}

	
	bool Object::equals(const Object &other) const {
		return this == &other;
	}

    
	TypeInfo Object::getTypeInfo() const {
		return TypeId<Object>();
	}
	
	
	bool Object::isClonable() const {
        return false;
    }
    
    
    Object* Object::clone() const {
        throw std::logic_error("Object::clone is not implemented.");
    }
    
    
    bool Object::isSerializable() const {
        return false;
    }

    
    void Object::serialize(xe::io::Stream *outStream) const {
        throw std::logic_error("Object::serialize must be implemented.");
    }

    
    bool Object::isDeserializable() const {
        return false;
    }

    
    void Object::deserialize(const xe::io::Stream *inStream) {
        throw std::logic_error("Object::deserialize must be implemented.");
    }
}
