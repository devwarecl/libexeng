
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

    void* BufferFI::lock(BufferUsage::Enum mode) {
#if defined(EXENG_DEBUG)
        std::uint8_t* pixels = ::FreeImage_GetBits(image->getBitmap());

        for (int i=0; i<120; i++) {
            std::cout << pixels[i];

            if ((i+1)%12) {
                std::cout << std::endl;
            }
        }
#endif

        return ::FreeImage_GetBits(image->getBitmap());
    }

    void BufferFI::unlock() {}

    const void* BufferFI::lock() const {
#if defined(EXENG_DEBUG)
        std::uint8_t* pixels = ::FreeImage_GetBits(image->getBitmap());

        for (int i=0; i<120; i++) {
            std::cout << int(pixels[i]) << ", ";

            if ((i+1)%12 == 0) {
                std::cout << std::endl;
            }
        }
#endif

        return ::FreeImage_GetBits(image->getBitmap());
    }

    void BufferFI::unlock() const {
        const_cast<BufferFI*>(this)->unlock();
    }
}}
