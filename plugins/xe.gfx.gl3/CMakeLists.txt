
FIND_PACKAGE (OpenGL REQUIRED)
INCLUDE_DIRECTORIES (${OpenGL_INCLUDE_DIRS})
LINK_DIRECTORIES (${OpenGL_LIBRARY_DIR})

FIND_PACKAGE (glfw3 REQUIRED)
INCLUDE_DIRECTORIES (${GLFW3_INCLUDE_DIR})
LINK_DIRECTORIES (${GLFW3_LIBRARY_DIR})

SET (GL3Files
	src/xe/gfx/Locker.hpp					src/xe/gfx/Locker.cpp
	src/xe/gfx/MeshSubsetGL3.hpp			src/xe/gfx/MeshSubsetGL3.cpp
	src/xe/gfx/BufferGL3.hpp				src/xe/gfx/BufferGL3.cpp
	src/xe/gfx/TextureGL3.hpp				src/xe/gfx/TextureGL3.cpp
	src/xe/gfx/GraphicsDriverGL3.hpp		src/xe/gfx/GraphicsDriverGL3.cpp
	src/xe/gfx/GraphicsDriverFactoryGL3.hpp	src/xe/gfx/GraphicsDriverFactoryGL3.cpp
	src/xe/gfx/ShaderGL3.hpp				src/xe/gfx/ShaderGL3.cpp
	src/xe/gfx/ShaderProgramGL3.hpp			src/xe/gfx/ShaderProgramGL3.cpp
	src/xe/gfx/InputManagerGLFW.hpp			src/xe/gfx/InputManagerGLFW.cpp
	src/xe/gfx/DebugGL3.hpp					src/xe/gfx/DebugGL3.cpp
	src/xe/gfx/UtilGL3.hpp
	src/xe/gfx/BufferStatusGL3.hpp 
	src/xe/gfx/GL3.hpp 
	src/xe/gfx/gl_core_3_3.h                src/xe/gfx/gl_core_3_3.c
	src/xe/gfx/PluginGL3.hpp                src/xe/gfx/PluginGL3.cpp
)

SOURCE_GROUP (\\ FILES ${GL3Files})

ADD_LIBRARY (xe.gfx.gl3 SHARED ${GL3Files})

SET_PROPERTY(TARGET xe.gfx.gl3 PROPERTY CXX_STANDARD 14)

TARGET_LINK_LIBRARIES (xe.gfx.gl3 xe ${GLFW3_LIBRARY} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES})

INSTALL (
	TARGETS xe.gfx.gl3
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
)
