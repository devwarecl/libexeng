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

#include "Object.hpp"

namespace exeng {
	Object::~Object()  { }

	std::string	Object::toString() const {
        // By default, convert the direction address to a string
		std::stringstream ss;

		ss << "Object " << typeid(*this).name() << " at " << this;

		return ss.str();
	}
    
    
	Object* Object::clone() const { 
		throw std::runtime_error("Metodo Object::clone no reimplementado.");
	}


	bool Object::equals(const Object &other) const {
		return this == &other;
	}


	bool Object::lesserThan(const Object& other) const {
        throw std::runtime_error("Must reimplement the method Object::lesserThan.");
	}


	void Object::assign(const Object& other) {
		throw std::runtime_error("Must reimplement the method Object::assign.");
	}


	bool Object::operator == (const Object& other) const {
		return this->equals(other);
	}

		
	bool Object::operator != (const Object& other) const {
		return !this->equals(other);
	}

		
	bool Object::operator < (const Object& other) const {
		return this->lesserThan(other);
	}

		
	bool Object::operator > (const Object& other) const {
		return !(this->equals(other) || this->lesserThan(other));
	}

		
	bool Object::operator <= (const Object& other) const {
		return this->equals(other) || this->lesserThan(other);
	}

		
	bool Object::operator >= (const Object& other) const {
		return !this->lesserThan(other);
	}


	Object& Object::operator= (const Object& other) {
		this->assign(other);
		return *this;
	}


	TypeInfo Object::getTypeInfo() const {
        return TypeInfo::get<Object>();
	}
}
