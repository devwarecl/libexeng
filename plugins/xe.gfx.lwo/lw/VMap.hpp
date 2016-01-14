
#pragma once

#ifndef __lw_vmap_hpp__
#define __lw_vmap_hpp__

#include <string>
#include "Collection.hpp"
#include "lwo/lwo2.h"

namespace lw {
	class VMap : public Collection<VMap, ::lwVMap> {
	public:
		VMap();
		explicit VMap(::lwVMap *vmap);

		std::string name() const;

		int dim() const;

		unsigned int type() const;

		VMap next() const;

		VMap prev() const;

		int* pindex() const;

		VMap find(const std::string &name, unsigned int type) const;

		float* val(const int index) const;

		int* vindex() const;
	};
}

#endif
