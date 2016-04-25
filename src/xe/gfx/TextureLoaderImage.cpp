
#include "TextureLoaderImage.hpp"

#include <xe/gfx/GraphicsDriver.hpp>

namespace xe { namespace gfx {
	
	TextureLoaderImage::TextureLoaderImage(ImageLoader *imageLoader_) : imageLoader(imageLoader_) {}
 
	TextureLoaderImage::~TextureLoaderImage() {}

	bool TextureLoaderImage::isSupported(const std::string &uri) {
		return true;
	}

	TexturePtr TextureLoaderImage::load(const std::string &uri) {
		//Image *image = this->imageLoader->getImage(uri);

		//if (!image) {
		//	return TexturePtr();
		//}

		//return this->getGraphicsDriver()->createTexture(image);

        return TexturePtr();
	}
}}
