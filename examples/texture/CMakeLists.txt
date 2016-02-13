
set (texture_src texture.cpp)

source_group(\\ FILES ${texture_src})

add_executable(texture ${texture_src})

set_property(TARGET texture PROPERTY CXX_STANDARD 14)

target_link_libraries(texture xe)

install (
	TARGETS texture
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
