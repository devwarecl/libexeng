
#pragma once

#ifndef __lw_object_hpp__
#define __lw_object_hpp__

#include "lw/lwo/lwo2.h"
#include "lw/Pointer.hpp"
#include "lw/List.hpp"

namespace lw {
	class Object : public Pointer<::lwObject> {
	public:
		Object();
		explicit Object(::lwObject *value);

		List<::lwSurface> surfaces() const;

		List<::lwLayer> layers() const;

		virtual ~Object();
	};
}

#endif
