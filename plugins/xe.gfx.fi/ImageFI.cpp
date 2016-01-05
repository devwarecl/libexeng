
#include "ImageFI.hpp"
#include "BufferFI.hpp"

namespace xe { namespace gfx {

	ImageFI::ImageFI(::FIBITMAP *bitmap_) : bitmap(bitmap_), buffer(this) {}

	ImageFI::~ImageFI() {
		if (bitmap) {
			::FreeImage_Unload(this->bitmap);
		}
	}

	Buffer* ImageFI::getBuffer() {
		return &buffer;
	}

	const Buffer* ImageFI::getBuffer() const {
		return &buffer;
	}

	ImageType::Enum ImageFI::getType() const {
		return ImageType::Img2D;
	}

	PixelFormat::Enum ImageFI::getFormat() const {
		switch (::FreeImage_GetBPP(this->bitmap)) {

			case 16: {
				bool red = FreeImage_GetRedMask(bitmap) == FI16_565_RED_MASK;
				bool green = FreeImage_GetGreenMask(bitmap) == FI16_565_GREEN_MASK;
				bool blue = FreeImage_GetBlueMask(bitmap) == FI16_565_BLUE_MASK;

				if (red && green && blue) {
					return PixelFormat::R5G5B5X1;
				} else {
					return PixelFormat::R5G6B5;
				}
			}
			
			case 24: return PixelFormat::R8G8B8;
		
			case 32: return PixelFormat::R8G8B8A8;
			
			default: return PixelFormat::Unknown;
		}
	}

	Vector3i ImageFI::getSize() const {
		return Vector3i (
			::FreeImage_GetWidth(bitmap),
			::FreeImage_GetHeight(bitmap),
			1
		);
	}

	FIBITMAP* ImageFI::getBitmap() {
		return this->bitmap;
	}

	const FIBITMAP* ImageFI::getBitmap() const {
		return this->bitmap;
	}
}}
