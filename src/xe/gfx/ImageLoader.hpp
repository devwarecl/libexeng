
#pragma once

#ifndef __xe_gfx_imageloader_hpp__
#define __xe_gfx_imageloader_hpp__

#include <xe/gfx/Image.hpp>

namespace xe { namespace gfx {
	/**
	 * @brief Image loader class.
	 * 
	 * Abstracts the image toolkit used to load and store the images.
	 */
	class EXENGAPI ImageLoader {
	public:
		virtual ~ImageLoader();

		virtual Image* getImage(const std::string &uri) = 0;

		virtual const Image* getImage(const std::string &uri) const = 0;
	};
}}

#endif
