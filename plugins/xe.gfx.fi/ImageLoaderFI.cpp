
#include "ImageLoaderFI.hpp"
#include "ImageFI.hpp"

#include <FreeImage.h>

namespace xe { namespace gfx {

	ImageLoaderFI::ImageLoaderFI() {
		::FreeImage_Initialise();
	}

	ImageLoaderFI::~ImageLoaderFI() {
		::FreeImage_DeInitialise();
	}

	Image* ImageLoaderFI::getImage(const std::string &uri) {
		return manager.getProduct(uri);
	}

	const Image* ImageLoaderFI::getImage(const std::string &uri) const {
		return nullptr;
	}

	ImagePtr ImageLoaderFI::load(const std::string &uri) {
		FREE_IMAGE_FORMAT format = ::FreeImage_GetFileType(uri.c_str());
		FIBITMAP *bitmap = ::FreeImage_Load(format, uri.c_str());
		ImagePtr image = std::make_unique<ImageFI>(bitmap);

		return image;
	}

	bool ImageLoaderFI::isSupported(const std::string &uri) {
		FREE_IMAGE_FORMAT format = ::FreeImage_GetFileType(uri.c_str());

		return format != FIF_UNKNOWN;
	}
}}
