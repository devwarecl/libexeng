
#pragma once

#ifndef __xe_gfx_imagefi_hpp__
#define __xe_gfx_imagefi_hpp__

#include <FreeImage.h>
#include <xe/gfx/Image.hpp>

#include "BufferFI.hpp"

namespace xe { namespace gfx {

	class ImageFI : public Image {
	public:
		explicit ImageFI(::FIBITMAP *bitmap);

		virtual ~ImageFI();

		virtual Buffer* getBuffer() override;

		virtual const Buffer* getBuffer() const override;

		virtual ImageType::Enum getType() const override;

		virtual PixelFormat::Enum getFormat() const override;

		virtual Vector3i getSize() const override;

		FIBITMAP* getBitmap();

		const FIBITMAP* getBitmap() const;

	private:
		::FIBITMAP *bitmap = nullptr;
		BufferFI buffer;
	};
}}

#endif
