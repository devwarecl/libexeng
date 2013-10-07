/**
 * @file GL3Debug.hpp
 * @brief Definition of OpenGL debugging routines and macros.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_GL3_DEBUG_HPP__
#define __EXENG_GRAPHICS_GL3_DEBUG_HPP__

namespace exeng { namespace graphics { namespace gl3 {

/**
 * @brief Check the OpenGL global error value.
 */
void checkGLError(const char *file, int line);

}}}

#define GL3_CHECK() exeng::graphics::gl3::checkGLError(__FILE__, __LINE__)

#endif  // __EXENG_GRAPHICS_GL3_DEBUG_HPP__
