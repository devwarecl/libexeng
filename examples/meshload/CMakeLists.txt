
set (meshload_src 
	meshload.cpp 
	fshader.hpp fshader.cpp 
	vshader.hpp vshader.cpp 
	RasterRenderer.hpp RasterRenderer.cpp
)

source_group(\\ FILES ${meshload_src})

add_executable(meshload ${meshload_src})

set_property(TARGET meshload PROPERTY CXX_STANDARD 14)

target_link_libraries(meshload xe)

install (
	TARGETS meshload
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
