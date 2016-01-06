
# IF (UNIX AND NOT APPLE)
#     ADD_DEFINITIONS(-fPIC )
# ENDIF()

SET (src_lwo
	lwo2.h
	clip.c 
	envelope.c 
	list.c 
	lwio.c 
	lwo2.c
	lwob.c
	pntspols.c
	surface.c
	vecmath.c
	vmap.c 
)

SET (src
	MeshLoaderLWO.hpp MeshLoaderLWO.cpp
	PluginLWO.cpp
)

SOURCE_GROUP(\\ FILES ${src})
SOURCE_GROUP(\\lwo FILES ${src_lwo})

ADD_LIBRARY(xe.gfx.lwo xe ${src_lwo} ${src_lwo})
