
# Software based raytracer pipeline

add_definitions(-DEXENG_BUILD)

set (target_name xe.sg.sw)
set (target_headers SoftwarePipeline.hpp)
set (target_sources SoftwarePipeline.cpp)
set (target_files ${target_headers} ${target_sources})

add_library(${target_name} SHARED ${target_files})

target_link_libraries(${target_name} xe)

source_group(\\ FILES ${target_files})

install (
	TARGETS ${target_name} 
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)

install (FILES SoftwarePipeline.hpp DESTINATION include/xe/sg)
