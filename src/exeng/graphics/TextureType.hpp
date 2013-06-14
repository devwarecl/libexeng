/**
 * @file TextureType.hpp
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_TEXTURETYPE_HPP__
#define __EXENG_GRAPHICS_TEXTURETYPE_HPP__

namespace exeng {
namespace graphics {

/**
 * @brief Type of texture.
 */
enum class TextureType {
    Tex1D,
    Tex2D,
    Tex3D,
    TexCubeMap
};


}
}

#endif  // __EXENG_GRAPHICS_TEXTURETYPE_HPP__
