
set (geogen_src geogen.cpp)

source_group(\\ FILES ${geogen_src})

add_executable(geogen ${geogen_src})

set_property(TARGET geogen PROPERTY CXX_STANDARD 14)

target_link_libraries(geogen xe)

install (
	TARGETS geogen
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
