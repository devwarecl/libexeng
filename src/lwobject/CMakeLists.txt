
include_directories(${PROJECT_SOURCE_DIR}/src/lwobject)

if (UNIX AND NOT APPLE)
    add_definitions(-fPIC )
endif()

set (source_files 
    
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

source_group(\\ FILES ${source_files})

add_library(lwobject ${source_files})
