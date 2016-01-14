
#include "Layer.hpp"

namespace lw {
	Layer::Layer() {}
	Layer::Layer(::lwLayer *layer) : Collection<Layer, ::lwLayer>(layer) {}

	VMap Layer::vmap() const {
		return VMap(this->value->vmap);
	}

	xe::Boxf Layer::bbox() const {
		const xe::Vector3f min_(&this->value->bbox[0]);
		const xe::Vector3f max_(&this->value->bbox[3]);
		const xe::Boxf box(min_, max_);

		return box;
	}

	int Layer::flags() const {
		return this->value->flags;
	}

	int Layer::index() const {
		return this->value->index;
	}

	VMap Layer::findVMap(const std::string &name, bool continuous) const {
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

	PolygonList Layer::polygon() const {
		return PolygonList(&this->value->polygon);
	}


	PointList Layer::points() const {
		return PointList(&this->value->point);
	}
}
