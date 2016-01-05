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
