/**
 * @file GL3BufferStatus.hpp
 * @brief Definition of the GL3BufferStatus class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_GL3_BUFFERSTATUS_HPP__
#define __EXENG_GRAPHICS_GL3_BUFFERSTATUS_HPP__

#include "GL3.hpp"

namespace exeng {
    namespace graphics {
        namespace gl3 {
            
            template<GLenum BufferTarget>
            struct BufferTargetMap;
            
            template<>
            struct BufferTargetMap<GL_ARRAY_BUFFER> {
                enum {Enum = GL_ARRAY_BUFFER_BINDING };
            };
            
            /**
             * @brief Preserves the name of the currently used buffer, and 
             * restores it after destruction.
             */
            template<GLenum BufferTarget>
            struct BufferStatus {
                GLint oldName;
                
                
                inline BufferStatus() {
                    GLenum Enum = 0;
                    Enum = BufferTargetMap<BufferTarget>::Enum;
                    ::glGetIntegerv(Enum, &oldName);
                }
                
                
                inline ~BufferStatus() {
                    ::glBindBuffer(BufferTarget, oldName);
                }
            };
        }
    }
}

#endif // __EXENG_GRAPHICS_GL3_HPP__
