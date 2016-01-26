
IF (NOT FREEIMAGE_INCLUDE_DIRS)
    MESSAGE(FATAL_ERROR "Please define the location of the FreeImage include directory.")
ENDIF()

INCLUDE_DIRECTORIES(${FREEIMAGE_INCLUDE_DIRS})
LINK_DIRECTORIES(${FREEIMAGE_LIBRARY_DIR})

SET (xe_gfx_fi_src
	ImageLoaderFI.hpp ImageLoaderFI.cpp 
	ImageFI.hpp ImageFI.cpp 
	BufferFI.hpp BufferFI.cpp 	
	PluginFI.cpp
)

SOURCE_GROUP(\\ FILES ${xe_gfx_fi_src})

ADD_LIBRARY(xe.gfx.fi SHARED ${xe_gfx_fi_src})

SET_PROPERTY (TARGET xe.gfx.fi PROPERTY CXX_STANDARD 14)

TARGET_LINK_LIBRARIES(xe.gfx.fi xe freeimage)

INSTALL (
	TARGETS xe.gfx.fi
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
