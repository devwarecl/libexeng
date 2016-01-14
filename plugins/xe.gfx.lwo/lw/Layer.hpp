
#pragma once

#ifndef __lw_layer_hpp__
#define __lw_layer_hpp__

#include <xe/Boundary.hpp>
#include "Collection.hpp"
#include "VMap.hpp"
#include "PolygonList.hpp"
#include "PointList.hpp"

namespace lw {	
	class Layer : public Collection<Layer, ::lwLayer> {
	public:
		Layer();
		explicit Layer(::lwLayer *layer);

		VMap vmap() const;

		xe::Boxf bbox() const;

		int flags() const;

		int index() const;

		VMap findVMap(const std::string &name, bool continuous) const;

		PolygonList polygon() const;

		PointList points() const;
	};
}

#endif
