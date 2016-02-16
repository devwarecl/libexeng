
FIND_PACKAGE (OpenGL REQUIRED)
INCLUDE_DIRECTORIES (${OpenGL_INCLUDE_DIRS})
LINK_DIRECTORIES (${OpenGL_LIBRARY_DIR})

FIND_PACKAGE (glfw3 REQUIRED)
INCLUDE_DIRECTORIES (${GLFW3_INCLUDE_DIR})
LINK_DIRECTORIES (${GLFW3_LIBRARY_DIR})

SET (GL3Files
	gl3/Locker.hpp                      gl3/Locker.cpp
	gl3/MeshSubsetGL3.hpp               gl3/MeshSubsetGL3.cpp
	gl3/BufferGL3.hpp                   gl3/BufferGL3.cpp
	gl3/TextureGL3.hpp                  gl3/TextureGL3.cpp
    gl3/TextureBufferGL3.hpp			gl3/TextureBufferGL3.cpp
	gl3/GraphicsDriverGL3.hpp           gl3/GraphicsDriverGL3.cpp
	gl3/GraphicsDriverFactoryGL3.hpp	gl3/GraphicsDriverFactoryGL3.cpp
	gl3/ShaderGL3.hpp                   gl3/ShaderGL3.cpp
	gl3/ShaderProgramGL3.hpp			gl3/ShaderProgramGL3.cpp
	gl3/InputManagerGLFW.hpp			gl3/InputManagerGLFW.cpp
	gl3/DebugGL3.hpp					gl3/DebugGL3.cpp
	gl3/UtilGL3.hpp
	gl3/BufferStatusGL3.hpp 
	gl3/GL3.hpp 
	gl3/gl_core_3_3.h                   gl3/gl_core_3_3.c
	gl3/PluginGL3.hpp                   gl3/PluginGL3.cpp
	gl3/Context.hpp                     gl3/Context.cpp
)

SOURCE_GROUP (\\gl3 FILES ${GL3Files})

ADD_LIBRARY (xe.gfx.gl3 SHARED ${GL3Files})

SET_PROPERTY(TARGET xe.gfx.gl3 PROPERTY CXX_STANDARD 14)

TARGET_LINK_LIBRARIES (xe.gfx.gl3 xe ${GLFW3_LIBRARY} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES})

INSTALL (
	TARGETS xe.gfx.gl3
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
)

