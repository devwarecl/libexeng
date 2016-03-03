
#include <cstdint>
#include <xe/Config.hpp>
#include "Context.hpp"

// define appropiate options for the glfw3native.h header
#if defined(EXENG_WINDOWS)
  #define GLFW_EXPOSE_NATIVE_WIN32
  #define GLFW_EXPOSE_NATIVE_WGL
  
  #include <GLFW/glfw3native.h>
  
#elif defined(EXENG_UNIX)
  #define GLFW_EXPOSE_NATIVE_X11
  #define GLFW_EXPOSE_NATIVE_GLX
  
  #include <GLFW/glfw3native.h>
  
#elif defined(EXENG_MACOS)
  #define GLFW_EXPOSE_NATIVE_NSGL
  #define GLFW_EXPOSE_NATIVE_COCOA
  
  #include <GLFW/glfw3native.h>
#endif 

// define the local ::getHandle function for the selected 
// window system and context handling
#if defined(EXENG_WINDOWS)
  #define GLFW_EXPOSE_NATIVE_WIN32
  #define GLFW_EXPOSE_NATIVE_WGL
  
static intptr_t  getGLContext(GLFWwindow *window) {
    intptr_t ctx = reinterpret_cast<intptr_t >(::glfwGetWGLContext(window));
    return ctx;
}

static intptr_t getOSContext(GLFWwindow *window) {
	return (intptr_t)::GetDC(::glfwGetWin32Window(window));
}

#elif defined(EXENG_UNIX)
  #define GLFW_EXPOSE_NATIVE_X11
  #define GLFW_EXPOSE_NATIVE_GLX
  
static intptr_t  getGLContext(GLFWwindow *window) {
    intptr_t  ctx = reinterpret_cast<std::uint64_t>(::glfwGetGLXContext(window));
    return ctx;
}

static intptr_t getOSContext(GLFWwindow *window) {
	return 0;
}

#elif defined(EXENG_MACOS)

#else 
static intptr_t getGLContext(GLFWwindow *window) {
    return 0;
}

static intptr_t getOSContext(GLFWwindow *window) {
	return 0;
}

#endif 

namespace xe { namespace gfx { namespace gl3 {
    Context::Context(GLFWwindow *window_) {
        window = window_;
    }
        
    Context::~Context() {
        if (window) {
            ::glfwDestroyWindow(window);
            window = nullptr;
        }
    }

    intptr_t Context::getGLContext() const {
        return ::getGLContext(window);
    }

	intptr_t Context::getOSContext() const {
		return ::getOSContext(window);
	}
}}}
