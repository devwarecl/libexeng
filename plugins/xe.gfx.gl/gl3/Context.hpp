
#pragma once

#ifndef __xe_gfx_gl3_context_hpp__
#define __xe_gfx_gl3_context_hpp__

#include <GLFW/glfw3.h>

namespace xe { namespace gfx { namespace gl3 {
    struct Context {
    public:
        Context() {}
        explicit Context(GLFWwindow *window);
        
        ~Context();
        
        intptr_t getGLContext() const;

		intptr_t getOSContext() const;
        
        GLFWwindow *window = nullptr;
    };
}}}

#endif 
