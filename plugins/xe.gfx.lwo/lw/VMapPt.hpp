
#pragma once

#ifndef __lw_vmappt_hpp__
#define __lw_vmappt_hpp__

#include "Wrapper.hpp"
#include "VMap.hpp"

namespace lw {	
	class VMapPt : public Wrapper<VMapPt, ::lwVMapPt> {
	public:
		VMapPt();
		VMapPt(::lwVMapPt *value);

		int index() const;

		VMap vmap() const;
	};
}

#endif
