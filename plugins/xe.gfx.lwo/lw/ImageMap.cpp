

#include "ImageMap.hpp"

namespace lw {
	ImageMap::ImageMap() {}
	ImageMap::ImageMap(::lwImageMap *value) : Wrapper<ImageMap, ::lwImageMap>(value) {}

	int ImageMap::aas_flags() const {
		return this->value->aas_flags;
	}

	float ImageMap::aa_strength() const {
		return this->value->aa_strength;
	}

	EParam ImageMap::amplitude() const {
		return EParam (&this->value->amplitude);
	}

	int ImageMap::axis() const {
		return this->value->axis;
	}

	int ImageMap::cindex() const {
		return this->value->cindex;
	}

	int ImageMap::projection() const {
		return this->value->projection;
	}

	EParam ImageMap::stck() const {
		return EParam(&this->value->stck);
	}

	std::string ImageMap::vmap_name() const {
		return this->value->vmap_name;
	}
		
	EParam ImageMap::wraph() const {
		return EParam(&this->value->wraph);
	}

	int ImageMap::wraph_type() const {
		return this->value->wraph_type;
	}

	EParam ImageMap::wrapw() const {
		return EParam(&this->value->wrapw);
	}

	int ImageMap::wrapw_type() const {
		return this->value->wrapw_type;
	}
}
