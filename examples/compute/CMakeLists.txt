
set (compute_src compute.cpp)

source_group(\\ FILES ${compute_src})

add_executable(compute ${compute_src})

set_property(TARGET compute PROPERTY CXX_STANDARD 14)

target_link_libraries(compute xe)

install (
	TARGETS compute
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
