
#pragma once

namespace lw {
	
	class Line : public Wrapper<Line, ::lwLine> {
	public:
		Line() {}
		Line(::lwLine *value) : Wrapper<Line, ::lwLine>(value) {}

		short enabled() const {
			return this->value->enabled;
		}

		unsigned short flags() const {
			return this->value->flags;
		}

		EParam size() const {
			return EParam(&this->value->size);
		}
	};

}
