
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
        
        std::uint64_t getHandle() const;
        
        GLFWwindow *window = nullptr;
    };
}}}

#endif 
