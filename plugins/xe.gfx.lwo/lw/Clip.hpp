
#pragma once

namespace lw {
	class Clip : public Collection<Clip, ::lwClip> {
	public:
		Clip() {}
		explicit Clip(::lwClip *clip) : Collection<Clip, ::lwClip>(clip) {}

		int index() const {
			return this->value->index;
		}

		Clip find(const int index) const {
			Clip result;

			for (const Clip &clip : *this) {
				if (clip.index() == index) {
					result = clip;
					break;
				}
			}

			return result;
		}
	};
}
