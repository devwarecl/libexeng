
#pragma once

#ifndef __lw_tmap_hpp__
#define __lw_tmap_hpp__

#include <xe/Enum.hpp>
#include <xe/Vector.hpp>
#include <xe/Matrix.hpp>
#include "Collection.hpp"
#include "VParam.hpp"

namespace lw {

	struct Proj : public xe::Enum {
		enum Enum {
			Planar,
			Cylindrical,
			Spherical,
			Cubic,
			Front,
			Map
		};
	};

	class TMap : public Collection<TMap, ::lwTMap> {
	public:
		TMap();
		explicit TMap(::lwTMap *value);

		VParam center() const;

		VParam rotate() const;

		VParam size() const;

		xe::Vector3f map_texcoord(Proj::Enum projection, const xe::Vector3f &point);
	};
}

#endif
