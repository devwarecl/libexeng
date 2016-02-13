
set (triangle_src triangle.cpp)

source_group(\\ FILES ${triangle_src})

add_executable(triangle ${triangle_src})

set_property(TARGET triangle PROPERTY CXX_STANDARD 14)

target_link_libraries(triangle xe)

install (
	TARGETS triangle
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
