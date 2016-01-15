
#include "Object.hpp"

namespace lw {
	Object::Object() {}
	Object::Object(::lwObject *value) : Pointer<::lwObject>(value) {}
	
	Object::~Object() {
		if (this->value) {
			::lwFreeObject(this->value);
		}
	}

	List<::lwSurface> Object::surfaces() const {
		return List<::lwSurface>(this->value->surf);
	}

	List<::lwLayer> Object::layers() const {
		return List<::lwLayer>(this->value->layer);
	}
}
