
#include "VMap.hpp"

namespace lw {
	VMap::VMap() {}
	VMap::VMap(::lwVMap *vmap) : Collection<VMap, ::lwVMap>(vmap) {}

	std::string VMap::name() const {
		return this->value->name;
	}

	int VMap::dim() const {
		return this->value->dim;
	}

	unsigned int VMap::type() const {
		return this->value->type;
	}

	VMap VMap::next() const {
		return VMap(this->value->next);
	}

	VMap VMap::prev() const {
		return VMap(this->value->prev);
	}

	int* VMap::pindex() const {
		return this->value->pindex;
	}

	VMap VMap::find(const std::string &name, unsigned int type) const {
		VMap result;

		for (const VMap &sibling : *this) {
			if (sibling.name() == name && sibling.type() == type) {
				result = sibling;
				break;
			}
		}

		if (!result && type == ID_TXUV) {
			VMap better_result = result.next().find(name, ID_TXUV);

			if (!better_result) {
				result = better_result;
			}
		}

		return result;
	}

	float* VMap::val(const int index) const {
		return this->value->val[index];
	}

	int* VMap::vindex() const {
		return this->value->vindex;
	}
}
