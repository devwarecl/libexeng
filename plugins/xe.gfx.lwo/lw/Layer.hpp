
#pragma once

#include <xe/Boundary.hpp>
#include "Collection.hpp"
#include "VMap.hpp"


namespace lw {
	
	class Layer : public Collection<Layer, ::lwLayer> {
	public:
		Layer() {}
		explicit Layer(::lwLayer *layer) : Collection<Layer, ::lwLayer>(layer) {}

		VMap vmap() const {
			return VMap(this->value->vmap);
		}

		xe::Boxf bbox() const {
			const xe::Vector3f min_(&this->value->bbox[0]);
			const xe::Vector3f max_(&this->value->bbox[3]);
			const xe::Boxf box(min_, max_);

			return box;
		}

		int flags() const {
			return this->value->flags;
		}

		int index() const {
			return this->value->index;
		}

		VMap findVMap(const std::string &name, bool continuous) const {
			VMap result;

			for (VMap vmap : this->vmap()) {
				const int* pindex = vmap.pindex();
				const bool found1 = continuous && !pindex;
				const bool found2 = !continuous && pindex;
				
				if (vmap.name() == name && (found1 || found2)) {
					result = vmap;
				}
			}

			return result;
		}
	};

}
