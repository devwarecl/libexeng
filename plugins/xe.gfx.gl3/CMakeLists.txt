
FIND_PACKAGE (OpenGL REQUIRED)
INCLUDE_DIRECTORIES (${OpenGL_INCLUDE_DIRS})
LINK_DIRECTORIES (${OpenGL_LIBRARY_DIR})

FIND_PACKAGE (glfw3 REQUIRED)
INCLUDE_DIRECTORIES (${GLFW3_INCLUDE_DIR})
LINK_DIRECTORIES (${GLFW3_LIBRARY_DIR})

SET (GL3Files
	src/xe/gfx/Locker.hpp					src/xe/gfx/Locker.cpp
	src/xe/gfx/GL3MeshSubset.hpp			src/xe/gfx/GL3MeshSubset.cpp
	src/xe/gfx/GL3Buffer.hpp				src/xe/gfx/GL3Buffer.cpp
	src/xe/gfx/GL3Texture.hpp				src/xe/gfx/GL3Texture.cpp
	src/xe/gfx/GL3GraphicsDriver.hpp		src/xe/gfx/GL3GraphicsDriver.cpp
	src/xe/gfx/GL3GraphicsDriverFactory.hpp	src/xe/gfx/GL3GraphicsDriverFactory.cpp
	src/xe/gfx/GL3Shader.hpp				src/xe/gfx/GL3Shader.cpp
	src/xe/gfx/GL3ShaderProgram.hpp			src/xe/gfx/GL3ShaderProgram.cpp
	src/xe/gfx/GL3Debug.hpp					src/xe/gfx/GL3Debug.cpp
	src/xe/gfx/GL3Utils.hpp
	src/xe/gfx/GL3BufferStatus.hpp 
	src/xe/gfx/GL3.hpp 
	src/xe/gfx/gl_core_3_3.h                src/xe/gfx/gl_core_3_3.c
	src/xe/gfx/GL3Plugin.hpp                src/xe/gfx/GL3Plugin.cpp
)

SOURCE_GROUP (\\ FILES ${GL3Files})

ADD_LIBRARY (xe.gfx.gl3 SHARED ${GL3Files})

TARGET_LINK_LIBRARIES (xe.gfx.gl3 xe ${GLFW3_LIBRARY} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES})

INSTALL (
	TARGETS xe.gfx.gl3
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
)
