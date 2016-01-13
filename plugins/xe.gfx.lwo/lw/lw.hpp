
#pragma once

#ifndef __lw_lwo_hpp__
#define __lw_lwo_hpp__

#include <cassert>
#include <string>
#include <xe/Vector.hpp>
#include <xe/Boundary.hpp>
#include "Collection.hpp"
#include "lwo/lwo2.h"

namespace lw {

	struct Proj {
		enum Enum {
			Planar,
			Cylindrical,
			Spherical,
			Cubic,
			Front,
			Map
		};
	};

	class Object : public Wrapper<Object, ::lwObject> {
	public:
		Object() {}
		Object(::lwObject *value) : Wrapper<Object, ::lwObject>(value) {}

		Surface surf() const {
			return Surface(this->value->surf);
		}

		Layer layer() const {
			return Layer(this->value->layer);
		}

		virtual ~Object() {
			if (this->value) {
				::lwFreeObject(this->value);
			}
		}
	};

	inline Texture TParam::tex() const {
		return Texture(this->value->tex);
	}
}

#endif
