
#include "Object.hpp"

namespace lw {
	Object::~Object() {
		if (ptr) {
			::lwFreeObject(ptr);
			ptr = nullptr;
		}
	}
}
