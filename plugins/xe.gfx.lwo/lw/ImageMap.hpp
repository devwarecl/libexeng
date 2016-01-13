
#pragma once

namespace lw {
	
	class ImageMap : public Wrapper<ImageMap, ::lwImageMap> {
	public:
		ImageMap() {}
		ImageMap(::lwImageMap *value) : Wrapper<ImageMap, ::lwImageMap>(value) {}

		int aas_flags() const {
			return this->value->aas_flags;
		}

		float aa_strength() const {
			return this->value->aa_strength;
		}

		EParam amplitude() const {
			return EParam (&this->value->amplitude);
		}

		int axis() const {
			return this->value->axis;
		}

		int cindex() const {
			return this->value->cindex;
		}

		int projection() const {
			return this->value->projection;
		}

		EParam stck() const {
			return EParam(&this->value->stck);
		}

		std::string vmap_name() const {
			return this->value->vmap_name;
		}
		
		EParam wraph() const {
			return EParam(&this->value->wraph);
		}

		int wraph_type() const {
			return this->value->wraph_type;
		}

		EParam wrapw() const {
			return EParam(&this->value->wrapw);
		}

		int wrapw_type() const {
			return this->value->wrapw_type;
		}
	};
}
