
#include "Line.hpp"

namespace lw {
	Line::Line() {}
	Line::Line(::lwLine *value) : Wrapper<Line, ::lwLine>(value) {}

	short Line::enabled() const {
		return this->value->enabled;
	}

	unsigned short Line::flags() const {
		return this->value->flags;
	}

	EParam Line::size() const {
		return EParam(&this->value->size);
	}
}
