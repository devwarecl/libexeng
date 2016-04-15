
set (target xe.demo)

set (target_src 
    Demo01.cpp 
    DemoApp.cpp DemoApp.hpp
    PhongPipeline.cpp PhongPipeline.hpp
)

source_group(\\ FILES ${target_src})

add_executable(${target} ${target_src})

# Target properties
set_property(TARGET ${target} PROPERTY CXX_STANDARD 14)

# Target linking libraries
target_link_libraries(${target} xe xe.main ${Boost_LIBRARIES})

install (
	TARGETS ${target}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
