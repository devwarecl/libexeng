
# IF (UNIX AND NOT APPLE)
#     ADD_DEFINITIONS(-fPIC )
# ENDIF()

INCLUDE_DIRECTORIES(lwo)

SET (src_lwo
	lwo/lwo2.h
	lwo/clip.c 
	lwo/envelope.c 
	lwo/list.c 
	lwo/lwio.c 
	lwo/lwo2.c
	lwo/lwob.c
	lwo/pntspols.c
	lwo/surface.c
	lwo/vecmath.c
	lwo/vmap.c 
)

SET (src
	MeshLoaderLWO.hpp MeshLoaderLWO.cpp
	PluginLWO.cpp
)

SOURCE_GROUP(\\ FILES ${src})
SOURCE_GROUP(\\lwo FILES ${src_lwo})

ADD_LIBRARY(xe.gfx.lwo SHARED ${src} ${src_lwo})

TARGET_LINK_LIBRARIES(xe.gfx.lwo xe)
