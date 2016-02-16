/**
 * @file GL3Debug.cpp
 * @brief Implementation of OpenGL 3 debugging routines.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <xe/Exception.hpp>
#include "DebugGL3.hpp"
#include "GL3.hpp"

#include <map>
#include <string>
#include <sstream>

namespace xe { namespace gfx { namespace gl3 {

    void checkGLError(const char *file, int line) {
		GLenum err = ::glGetError();

		if (err != GL_NO_ERROR) {
            std::string error;
			
            switch(err) {
                case GL_INVALID_OPERATION: error = "GL_INVALID_OPERATION"; break;
                case GL_INVALID_ENUM:      error = "GL_INVALID_ENUM";      break;
                case GL_INVALID_VALUE:     error = "GL_INVALID_VALUE";     break;
                case GL_OUT_OF_MEMORY:     error = "GL_OUT_OF_MEMORY";     break;
                    
                case GL_INVALID_FRAMEBUFFER_OPERATION:  
                    error = "GL_INVALID_FRAMEBUFFER_OPERATION";  
                    break;

				default:
					error = "Unknown GL error:" + std::to_string(err);
            }
			
			std::stringstream ss;
            ss << error << " - " << file << ":" << line << std::endl;
			EXENG_THROW_EXCEPTION(ss.str());
		}
    }
}}}
