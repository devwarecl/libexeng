
#pragma once

#ifndef __lw_vmap_hpp__
#define __lw_vmap_hpp__

#include <string>
#include "Collection.hpp"
#include "lwo/lwo2.h"

namespace lw {
	class VMap : public Collection<VMap, ::lwVMap> {
	public:
		VMap() {}
		explicit VMap(::lwVMap *vmap) : Collection<VMap, ::lwVMap>(vmap) {}

		std::string name() const {
			return this->value->name;
		}

		int dim() const {
			return this->value->dim;
		}

		unsigned int type() const {
			return this->value->type;
		}

		VMap next() const {
			return VMap(this->value->next);
		}

		VMap prev() const {
			return VMap(this->value->prev);
		}

		int* pindex() const {
			return this->value->pindex;
		}

		VMap find(const std::string &name, unsigned int type) const {
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

		float* val(const int index) const {
			return this->value->val[index];
		}

		int* vindex() const {
			return this->value->vindex;
		}
	};
}

#endif
