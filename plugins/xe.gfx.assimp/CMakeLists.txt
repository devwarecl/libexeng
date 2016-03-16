
find_package(assimp REQUIRED)

SET (xe_gfx_assimp_src
	PluginAssimp.hpp PluginAssimp.cpp 
	MeshLoaderAssimp.hpp MeshLoaderAssimp.cpp 
)

SOURCE_GROUP(\\ FILES ${xe_gfx_assimp_src})

include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})

ADD_LIBRARY(xe.gfx.assimp SHARED ${xe_gfx_assimp_src})

SET_PROPERTY (TARGET xe.gfx.assimp PROPERTY CXX_STANDARD 14)

TARGET_LINK_LIBRARIES(xe.gfx.assimp xe ${ASSIMP_LIBRARIES})

INSTALL (
	TARGETS xe.gfx.assimp
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
