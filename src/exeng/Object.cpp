
#include <cassert>
#include <typeinfo>
#include <sstream>
#include <stdexcept>

#include "Object.hpp"

namespace exeng {
	Object::~Object()  { }

	std::string	Object::toString() const {
		// Por defecto, devuelve el nombre del tipo dinamico que lo representa, junto con la 
		// direccion de memoria
		std::stringstream ss;

		ss << "Objeto " << typeid(*this).name() << " en " << this;

		return ss.str();
	}


	Object* Object::clone() const { 
		// Preferible lanzar una excepcion
		throw std::runtime_error("Metodo Object::clone no reimplementado.");
	}


	bool Object::equals(const Object &other) const {
		// Se deberia reimplementar este metodo
		return this == &other;
	}


	bool Object::lesserThan(const Object& other) const {
		// Solo devolver la comparacion de "menor que" para las direcciones de memoria 
		// de los objetos
		return this < &other;
	}


	void Object::assign(const Object& other) {
		throw std::runtime_error("Metodo Object::assign no reimplementado.");
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
		throw std::runtime_error("Metodo Object::getTypeInfo no reimplementado.");
	}
}
