
# IF (UNIX AND NOT APPLE)
#     ADD_DEFINITIONS(-fPIC )
# ENDIF()

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(lw)
INCLUDE_DIRECTORIES(lw/lwo)

SET (src_lw_lwo
	lw/lwo/lwo2.h
	lw/lwo/clip.c 
	lw/lwo/envelope.c 
	lw/lwo/list.c 
	lw/lwo/lwio.c 
	lw/lwo/lwo2.c
	lw/lwo/lwob.c
	lw/lwo/pntspols.c
	lw/lwo/surface.c
	lw/lwo/vecmath.c
	lw/lwo/vmap.c 
)

SET (src_lw
	lw/lw.hpp 
	lw/Array.hpp 
	lw/Collection.hpp 
	lw/Wrapper.hpp 
	lw/Axis.cpp			lw/Axis.hpp 
	lw/Clip.cpp			lw/Clip.hpp 
	lw/CParam.cpp		lw/CParam.hpp 
	lw/EParam.cpp		lw/EParam.hpp 
	lw/Gradient.cpp		lw/Gradient.hpp 
	lw/GradKey.cpp		lw/GradKey.hpp 
	lw/ImageMap.cpp		lw/ImageMap.hpp 
	lw/Layer.cpp		lw/Layer.hpp 
	lw/Line.cpp			lw/Line.hpp 
	lw/Object.cpp		lw/Object.hpp 
	lw/Plugin.cpp		lw/Plugin.hpp 
	lw/Point.cpp		lw/Point.hpp 
	lw/PointList.cpp	lw/PointList.hpp 
	lw/PolVert.cpp		lw/PolVert.hpp 
	lw/Polygon.cpp		lw/Polygon.hpp 
	lw/PolygonList.cpp	lw/PolygonList.hpp 
	lw/Procedural.cpp	lw/Procedural.hpp 
	lw/RMap.cpp			lw/RMap.hpp 
	lw/Surface.cpp		lw/Surface.hpp 
	lw/Texture.cpp		lw/Texture.hpp 
	lw/TMap.cpp			lw/TMap.hpp 
	lw/TParam.cpp		lw/TParam.hpp 
	lw/VMap.cpp			lw/VMap.hpp 
	lw/VMapPt.cpp		lw/VMapPt.hpp
	lw/VParam.cpp		lw/VParam.hpp
)

SET (src
	MeshLoaderLWO.cpp	MeshLoaderLWO.hpp 
	PluginLWO.cpp		PluginLWO.hpp
)

SOURCE_GROUP(\\			FILES ${src})
SOURCE_GROUP(\\lw		FILES ${src_lw})
SOURCE_GROUP(\\lw\\lwo	FILES ${src_lw_lwo})

ADD_LIBRARY(xe.gfx.lwo SHARED ${src} ${src_lw} ${src_lw_lwo})

TARGET_LINK_LIBRARIES(xe.gfx.lwo xe)

INSTALL (
	TARGETS xe.gfx.lwo
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
)
