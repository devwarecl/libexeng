
#pragma once

#ifndef __lw_clip_hpp__
#define __lw_clip_hpp__

#include "Collection.hpp"
#include "lwo/lwo2.h"

namespace lw {
	class Clip : public Collection<Clip, ::lwClip> {
	public:
		Clip();
		explicit Clip(::lwClip *clip);

		int index() const;

		Clip find(const int index) const;
	};
}

#endif 
