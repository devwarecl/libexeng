
#pragma once

#ifndef __xe_gfx_textureloaderimage_hpp__
#define __xe_gfx_textureloaderimage_hpp__

#include <xe/gfx/ImageLoader.hpp>
#include <xe/gfx/TextureLoader.hpp>

namespace xe { namespace gfx {
	class EXENGAPI TextureLoaderImage : public TextureLoader {
	public:
		explicit TextureLoaderImage(ImageLoader *imageLoader = nullptr);

		virtual ~TextureLoaderImage();

		virtual bool isSupported(const std::string &uri) override;

		virtual TexturePtr load(const std::string &uri) override;

	private:
		ImageLoader *imageLoader = nullptr;
	};
}}

#endif 
