#pragma once

#ifndef __xe_gfx_imateriallibrary_hpp__
#define __xe_gfx_imateriallibrary_hpp__

#include <xe/gfx/Forward.hpp>
#include <xe/gfx/Material.hpp>

namespace xe { namespace gfx {

	class EXENGAPI IMaterialLibrary {
	public:
		virtual ~IMaterialLibrary() {}

		virtual MaterialFormat getFormat() const = 0;

		virtual Material* createMaterial(const std::string &name) = 0;

		virtual Material* getMaterial(const std::string &name) = 0;
		virtual Material* getMaterial(const int index) = 0;

		virtual const Material* getMaterial(const std::string &name) const = 0;
		virtual const Material* getMaterial(const int index) const = 0;
		virtual const int getMaterialCount() const = 0;
		virtual const int getMaterialIndex(const Material *material) const = 0;
	};	
}}

#endif 
