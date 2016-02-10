
SET (xe_gfx_assimp_src
	PluginAssimp.hpp PluginAssimp.cpp 
)

SOURCE_GROUP(\\ FILES ${xe_gfx_assimp_src})

ADD_LIBRARY(xe.gfx.assimp SHARED ${xe_gfx_assimp_src})

SET_PROPERTY (TARGET xe.gfx.assimp PROPERTY CXX_STANDARD 14)

TARGET_LINK_LIBRARIES(xe.gfx.assimp xe)

INSTALL (
	TARGETS xe.gfx.assimp
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
