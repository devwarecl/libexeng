
#include "Clip.hpp"

namespace lw {
	Clip::Clip() {}

	Clip::Clip(::lwClip *clip) : Collection<Clip, ::lwClip>(clip) {}

	int Clip::index() const {
		return this->value->index;
	}

	Clip Clip::find(const int index) const {
		Clip result;

		for (const Clip &clip : *this) {
			if (clip.index() == index) {
				result = clip;
				break;
			}
		}

		return result;
	}
}
