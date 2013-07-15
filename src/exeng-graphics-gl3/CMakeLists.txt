include_directories( ${PROJECT_SOURCE_DIR}/src )

# TODO: Add find package for GLFW3 

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_library(exeng-graphics-gl3 SHARED
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

target_link_libraries(exeng-graphics-gl3 exeng glfw ${OpenGL_LIBRARIES} ${Boost_LIBRARIES})
