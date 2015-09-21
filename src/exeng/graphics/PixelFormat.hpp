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
#include <exeng/Config.hpp>
#include <exeng/TFlags.hpp>
#include <exeng/DataType.hpp>

namespace exeng { namespace graphics {
        
    //!
    enum class DepthFormat {
        Unknown,
        D8,
        D16,
        D24,
        D32
    };
        
    //!
    enum class StencilFormat {
        Unknown,
        S8,
        S16,
        S24,
        S32
    };
        
        
    struct PixelFormat {
            
    };
}}

#endif  //__EXENG_GRAPHICS_PIXELFORMAT_HPP__
