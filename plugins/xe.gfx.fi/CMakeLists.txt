
INCLUDE_DIRECTORIES(${FREE_IMAGE_ROOT})
LINK_DIRECTORIES(${FREE_IMAGE_ROOT})

ADD_LIBRARY(xe.gfx.fi SHARED 
	ImageLoaderFI.hpp ImageLoaderFI.cpp 
	ImageFI.hpp ImageFI.cpp 
	BufferFI.hpp BufferFI.cpp 	
	PluginFI.cpp
)

SET_PROPERTY (TARGET xe.gfx.fi PROPERTY CXX_STANDARD 14)

TARGET_LINK_LIBRARIES(xe.gfx.fi xe FreeImage)

INSTALL (
	TARGETS xe.gfx.fi
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
)
