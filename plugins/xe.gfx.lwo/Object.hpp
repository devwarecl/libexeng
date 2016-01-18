
#pragma once 

#ifndef __lw_object_hpp__
#define __lw_object_hpp__

#include <lwo2.h>

namespace lw {

	class Object {
	public:
		Object()  {}
		Object(::lwObject *other ) : ptr(other) {}

		~Object();

		::lwObject *getHandle() const {
			return ptr;
		}

	private:
		::lwObject *ptr = nullptr;
	};
}

#endif 
