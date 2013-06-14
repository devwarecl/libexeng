include_directories( ${PROJECT_SOURCE_DIR}/src )

# add_definitions(-DGLCOREARB_PROTOTYPES)

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

target_link_libraries(exeng-graphics-gl3 exeng glfw GL)
