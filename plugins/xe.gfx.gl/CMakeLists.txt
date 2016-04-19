
set (target xe.gfx.gl)

find_package(glbinding REQUIRED)

find_package (OpenGL REQUIRED)
include_directories (${OpenGL_INCLUDE_DIRS})
link_directories (${OpenGL_LIBRARY_DIR})

find_package (glfw3 REQUIRED)
include_directories (${GLFW3_INCLUDE_DIR})
link_directories (${GLFW3_LIBRARY_DIR})

set (gl2_files 
    gl2/GraphicsDriverGL2.hpp   gl2/GraphicsDriverGL2.cpp
)

set (gl3_files
    gl3/Locker.hpp                      gl3/Locker.cpp
    gl3/MeshSubsetGL3.hpp               gl3/MeshSubsetGL3.cpp
    gl3/BufferGL3.hpp                   gl3/BufferGL3.cpp
    gl3/TextureGL3.hpp                  gl3/TextureGL3.cpp
    gl3/TextureBufferGL3.hpp            gl3/TextureBufferGL3.cpp
    gl3/GraphicsDriverGL3.hpp           gl3/GraphicsDriverGL3.cpp
    gl3/GraphicsDriverFactoryGL3.hpp    gl3/GraphicsDriverFactoryGL3.cpp
    gl3/ShaderGL3.hpp                   gl3/ShaderGL3.cpp
    gl3/ShaderProgramGL3.hpp            gl3/ShaderProgramGL3.cpp
    gl3/InputManagerGLFW.hpp            gl3/InputManagerGLFW.cpp
    gl3/DebugGL3.hpp                    gl3/DebugGL3.cpp
    gl3/UtilGL3.hpp
    gl3/BufferStatusGL3.hpp 
    gl3/GL3.hpp 
    gl3/PluginGL3.hpp                   gl3/PluginGL3.cpp
    gl3/Context.hpp                     gl3/Context.cpp
)

source_group (\\gl3 FILES ${gl3_files})
source_group (\\gl2 FILES ${gl2_files})

add_library (${target} SHARED ${gl3_files} ${gl2_files})

set_property(TARGET ${target} PROPERTY CXX_STANDARD 14)

target_link_libraries (${target} 
    xe 
    ${GLFW3_LIBRARY} 
    ${OPENGL_LIBRARIES} 
    ${Boost_LIBRARIES}
    glbinding    
)

install (
    TARGETS ${target}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
)
