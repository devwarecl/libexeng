
#pragma once

#ifndef __lw_line_hpp__
#define __lw_line_hpp__

#include "Wrapper.hpp"
#include "EParam.hpp"

namespace lw {
	
	class Line : public Wrapper<Line, ::lwLine> {
	public:
		Line();
		Line(::lwLine *value);

		short enabled() const;

		unsigned short flags() const;

		EParam size() const;
	};
}

#endif 
