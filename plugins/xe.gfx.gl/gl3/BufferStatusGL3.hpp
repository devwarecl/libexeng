/**
 * @file BufferGL3Status.hpp
 * @brief Definition of the BufferGL3Status class.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_GL3_BUFFERSTATUS_HPP__
#define __EXENG_GRAPHICS_GL3_BUFFERSTATUS_HPP__

#include <cassert>
#include "GL3.hpp"

namespace xe { namespace gfx { namespace gl3 {
	/*
    inline GLenum targetToBinding(GLenum target) {
        switch (target) {
            case GL_ARRAY_BUFFER:           return GL_ARRAY_BUFFER_BINDING;
            case GL_ELEMENT_ARRAY_BUFFER:   return GL_ELEMENT_ARRAY_BUFFER_BINDING;
            default:                        assert(false);
        }

        return 0;
    }
	*/

    /**
     * @brief Preserves the name of the currently used buffer, and 
     * restores it after destruction.
     */
	/*
    struct BufferStatus {
        GLint bufferId = 0;
        GLuint target = 0;
        
        inline BufferStatus(GLuint target_) : target(target_) {
            ::glGetIntegerv(targetToBinding(target), &bufferId);
        }
        
        inline ~BufferStatus() {
            ::glBindBuffer(target, bufferId);
        }
    };
	*/
}}}

#endif // __EXENG_GRAPHICS_GL3_HPP__
