
#pragma once

#ifndef __lw_object_hpp__
#define __lw_object_hpp__

#include "Surface.hpp"
#include "Layer.hpp"

namespace lw {
	class Object : public Wrapper<Object, ::lwObject> {
	public:
		Object();
		Object(::lwObject *value);

		Surface surf() const;

		Layer layer() const;

		virtual ~Object();
	};
}

#endif
