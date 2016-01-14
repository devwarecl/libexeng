
#include "VMapPt.hpp"

namespace lw {
	VMapPt::VMapPt() {}
	VMapPt::VMapPt(::lwVMapPt *value) : Wrapper<VMapPt, ::lwVMapPt>(value) {}

	int VMapPt::index() const {
		return this->value->index;
	}

	VMap VMapPt::vmap() const {
		return VMap(this->value->vmap);
	}
}
