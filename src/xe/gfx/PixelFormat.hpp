/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_PIXELFORMAT_HPP__
#define __EXENG_GRAPHICS_PIXELFORMAT_HPP__

#include <cstdint>
#include <array>
#include <xe/Config.hpp>
#include <xe/TFlags.hpp>
#include <xe/DataType.hpp>

namespace xe { namespace gfx {
    
	/** 
	 * @brief The image pixel format
	 */
	struct PixelFormat : public Enum {
		enum Enum {
			Unknown,
			R5G5B5X1,
			R5G5B5A1,
			R5G6B5,
			R8G8B8,
			R8G8B8A8,
		};

		inline static int size(PixelFormat::Enum format) {
			switch (format) {
			case R5G5B5X1:
			case R5G5B5A1:
			case R5G6B5:
				return 16;

			case R8G8B8:
				return 24;

			case R8G8B8A8:
				return 32;

			default:
				return 0;
			}
		}
	};

	/*
    struct DepthFormat : public Enum {
		enum Enum {
			Unknown,
			D16,
			D24,
		};
    };
       
    struct StencilFormat : public Enum {
		enum Enum {
			Unknown,
			S16,
			S24,
			S32
		};
    };
	*/
}}

#endif  //__EXENG_GRAPHICS_PIXELFORMAT_HPP__
