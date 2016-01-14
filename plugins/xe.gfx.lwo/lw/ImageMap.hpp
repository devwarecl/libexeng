
#pragma once

#ifndef __lw_imagemap_hpp__
#define __lw_imagemap_hpp__

#include <string>
#include "Wrapper.hpp"
#include "EParam.hpp"

namespace lw {
	
	class ImageMap : public Wrapper<ImageMap, ::lwImageMap> {
	public:
		ImageMap();
		ImageMap(::lwImageMap *value);

		int aas_flags() const;

		float aa_strength() const;

		EParam amplitude() const;

		int axis() const;

		int cindex() const;

		int projection() const;

		EParam stck() const;

		std::string vmap_name() const;
		
		EParam wraph() const;

		int wraph_type() const;

		EParam wrapw() const;

		int wrapw_type() const;
	};
}

#endif 
