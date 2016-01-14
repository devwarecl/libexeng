
#pragma once

#ifndef __xe_surface_hpp__
#define __xe_surface_hpp__

#include "Collection.hpp"
#include "EParam.hpp"
#include "TParam.hpp"
#include "CParam.hpp"
#include "Line.hpp"
#include "RMap.hpp"
#include "Plugin.hpp"

namespace lw {
	
	class Surface : public Collection<Surface, ::lwSurface> {
	public:
		Surface();
		Surface(::lwSurface *value);

		EParam add_trans() const;

		float alpha() const;

		int alpha_mode() const;

		TParam bump() const;

		CParam color() const;

		EParam color_filter() const;

		EParam color_hilite() const;

		TParam diffuse() const;
		
		EParam dif_sharp() const;

		TParam eta() const;

		TParam glossiness() const;

		EParam glow() const;

		Line line() const;

		TParam luminosity() const;

		std::string name() const;

		int nshaders() const;

		RMap reflection() const;

		Plugin shader() const;

		int sideflags() const;

		float smooth() const;

		TParam specularity() const;

		std::string srcname() const;

		TParam translucency() const;

		RMap transparency() const;
	};
}

#endif
