
#include "BufferFI.hpp"
#include "ImageFI.hpp"

namespace xe { namespace gfx {

	BufferFI::BufferFI(ImageFI *image_) : image(image_) {}

	int BufferFI::getHandle() const {
		return 0;
	}

	int BufferFI::getSize() const {
		Vector3i size = this->image->getSize();
		const int volume = size.x * size.y * size.z;

		return ::FreeImage_GetPitch(this->image->getBitmap()) * volume;
	}

	void* BufferFI::getPointer() {
		return ::FreeImage_GetBits(this->image->getBitmap());
	}

	const void* BufferFI::getPointer() const {
		return ::FreeImage_GetBits(this->image->getBitmap());
	}
}}
