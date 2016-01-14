
#include "Object.hpp"

namespace lw {
	Object::Object() {}
	Object::Object(::lwObject *value) : Wrapper<Object, ::lwObject>(value) {}
	
	Object::~Object() {
		if (this->value) {
			::lwFreeObject(this->value);
		}
	}
	Surface Object::surf() const {
		return Surface(this->value->surf);
	}

	Layer Object::layer() const {
		return Layer(this->value->layer);
	}
}
