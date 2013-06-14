/**
 * @file ShaderType.hpp
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_SHADERTYPE_HPP__
#define __EXENG_GRAPHICS_SHADERTYPE_HPP__

namespace exeng {
namespace graphics {

/**
 * @brief The type of shader
 */
enum class ShaderType {
    Vertex,
    Fragment,
    Geometry
};

}
}

#endif  // __EXENG_GRAPHICS_SHADERTYPE_HPP__
