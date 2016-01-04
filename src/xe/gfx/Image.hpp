
/**
 * @file Image.hpp
 * @brief Image abstract class declaration
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#pragma once

#ifndef __EXENG_GRAPHICS_IMAGE_HPP__
#define __EXENG_GRAPHICS_IMAGE_HPP__

#include <memory>
#include <xe/Buffer.hpp>
#include <xe/Vector.hpp>
#include <xe/Object.hpp>
#include <xe/gfx/PixelFormat.hpp>
#include <xe/gfx/PixelType.hpp>
#include <xe/gfx/ColorFormat.hpp>

namespace xe { namespace gfx {

	/** 
	 * @brief The image type
	 */
	struct ImageType : public Enum {
		enum Enum {
			Unknown,
			Img1D,
			Img2D,
			Img3D
		};
	};

	/** 
	 * @brief The image pixel format
	 */
	struct ImageFormat : public Enum {
		enum Enum {
			Unknown,
			R5G5B5X1,
			R5G5B5A1,
			R5G6B5,
			R8G8B8,
			R8G8B8A8,
		};
	};

	/** 
	 * @brief Image abstract class
	 */
    class EXENGAPI Image : public Object {
    public:
		virtual ~Image();

		virtual Buffer* getBuffer() = 0;

		virtual const Buffer* getBuffer() const = 0;

		virtual ImageType::Enum getType() const = 0;

		virtual ImageFormat::Enum getFormat() const = 0;

		virtual Vector3i getSize() const = 0;
    };

	typedef std::unique_ptr<Image> ImagePtr;
}}

#endif  //__EXENG_GRAPHICS_IMAGE_HPP__
