
set (simplemesh_src simplemesh.cpp)

source_group(\\ FILES ${simplemesh_src})

add_executable(simplemesh ${simplemesh_src})

set_property(TARGET simplemesh PROPERTY CXX_STANDARD 14)

target_link_libraries(simplemesh xe)

install (
	TARGETS simplemesh
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
