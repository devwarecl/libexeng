
#pragma once

#ifndef __xe_gfx_bufferfi_hpp__
#define __xe_gfx_bufferfi_hpp__

#include <xe/Buffer.hpp>

namespace xe { namespace gfx {

	class ImageFI;
	class BufferFI : public Buffer {
	public:
		explicit BufferFI(ImageFI *image);

		virtual int getHandle() const override;

		virtual int getSize() const override;

		virtual const void* getPointer() const override;

		virtual void* getPointer() override;

	private:
		ImageFI *image = nullptr;
	};
}}

#endif
