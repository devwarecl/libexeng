
#pragma once

#ifndef __lw_vmappt_hpp__
#define __lw_vmappt_hpp__

#include "Wrapper.hpp"
#include "VMap.hpp"

namespace lw {
	
	class VMapPt : public Wrapper<VMapPt, ::lwVMapPt> {
	public:
		VMapPt() {}
		VMapPt(::lwVMapPt *value) : Wrapper<VMapPt, ::lwVMapPt>(value) {}

		int index() const {
			return this->value->index;
		}

		VMap vmap() const {
			return VMap(this->value->vmap);
		}
	};
}

#endif
