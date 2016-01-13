
#pragma once

namespace lw {
	
	class PolVert : public Wrapper<PolVert, ::lwPolVert> {
	public:
		PolVert() {}
		PolVert(::lwPolVert *value) : Wrapper<PolVert, ::lwPolVert>(value) {}

		int index() const {
			return this->value->index;
		}

		xe::Vector3f norm() const {
			return xe::Vector3f(&this->value->norm[0]);
		}

		int nvmaps() const {
			return this->value->nvmaps;
		}

		VMapPt vm(const int index) const {
			return VMapPt(&this->value->vm[index]);
		}
	};

}
