include_directories( ${PROJECT_SOURCE_DIR}/src )

find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED)
find_package(glfw REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OpenGL_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIR})

link_directories(${Boost_LIBRARY_DIRS})
link_directories(${GLFW_LIBRARY_DIR})
link_directories(${OpenGL_LIBRARY_DIR})

# FIXME: Use a module for GLFW 3 instead.
# if (NOT GLFW_LIBRARIES)
#   if (WIN32)
# 	set(GLFW_LIBRARIES "glfw3dll")
#   else()
#     set(GLFW_LIBRARIES "glfw")
#   endif()
# endif()

add_library(exeng.graphics.gl3 SHARED
	Locker.hpp Locker.cpp
	GL3VertexBuffer.hpp GL3VertexBuffer.cpp
	GL3Texture.hpp GL3Texture.cpp
	GL3IndexBuffer.hpp  GL3IndexBuffer.cpp
	GL3GraphicsDriver.hpp GL3GraphicsDriver.cpp
	GL3GraphicsDriverFactory.hpp GL3GraphicsDriverFactory.cpp
	GL3Shader.hpp GL3Shader.cpp
	GL3ShaderProgram.hpp GL3ShaderProgram.cpp
	GL3Debug.hpp GL3Debug.cpp
	GL3Plugin.hpp GL3Plugin.cpp
	GL3Utils.hpp GL3Utils.inl
	GL3BufferStatus.hpp 
	GL3.hpp 
	gl_core_3_3.h gl_core_3_3.c
)

target_link_libraries(exeng.graphics.gl3 exeng ${GLFW_LIBRARY} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES})
