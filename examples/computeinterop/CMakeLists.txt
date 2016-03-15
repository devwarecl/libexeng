
set (computeinterop_src 
	computeinterop.cpp
	ComputeInteropApp.hpp
	ComputeInteropApp.cpp
)

source_group(\\ FILES ${computeinterop_src})

add_executable(computeinterop ${computeinterop_src})

set_property(TARGET computeinterop PROPERTY CXX_STANDARD 14)

target_link_libraries(computeinterop xe)

install (
	TARGETS computeinterop
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
