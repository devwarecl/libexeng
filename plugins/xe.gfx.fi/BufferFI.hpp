
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

        virtual void* lock(BufferLockMode::Enum mode) override;

		virtual void unlock() override;

		virtual const void* lock() const override;

		virtual void unlock() const override;

	private:
		ImageFI *image = nullptr;
	};
}}

#endif
