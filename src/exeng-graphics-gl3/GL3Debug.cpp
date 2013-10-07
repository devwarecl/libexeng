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

#include "GL3Debug.hpp"
#include "GL3.hpp"

#include <map>
#include <iostream>

namespace exeng { namespace graphics { namespace gl3 {
void checkGLError(const char *file, int line) {

	const int maxErrorCount = 4;
	int errorCount = 0;

    GLenum err = ::glGetError();
    
    while(err!=GL_NO_ERROR && errorCount<maxErrorCount) {
		++errorCount;
        std::string error;
    
        switch(err) {
            case GL_INVALID_OPERATION: error = "INVALID_OPERATION"; break;
            case GL_INVALID_ENUM:      error = "INVALID_ENUM";      break;
            case GL_INVALID_VALUE:     error = "INVALID_VALUE";     break;
            case GL_OUT_OF_MEMORY:     error = "OUT_OF_MEMORY";     break;
                
            case GL_INVALID_FRAMEBUFFER_OPERATION:  
                error = "INVALID_FRAMEBUFFER_OPERATION";  
                break;
        }
    
        std::cout << "GL_" << error.c_str() << " - " << file << ":" << line << std::endl;
        
        err = ::glGetError();
    }
}

}}}