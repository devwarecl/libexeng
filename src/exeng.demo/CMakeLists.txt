
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# prepare resources filenames
SET (demo_resources_src Vertex.glsl Fragment.glsl Assets.xml)
SET (demo_resources )

# iterate over resource files for compilation
FOREACH(resource_src ${demo_resources_src})
	ADD_CUSTOM_COMMAND (
		OUTPUT	${CMAKE_CURRENT_BINARY_DIR}/${resource_src}.hpp 
				${CMAKE_CURRENT_BINARY_DIR}/${resource_src}.cpp 
		COMMAND file2cpp ${CMAKE_CURRENT_SOURCE_DIR}/${resource_src}
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${resource_src}
	)
	
	LIST (APPEND demo_resources ${resource_src}.hpp ${resource_src}.cpp)
ENDFOREACH(resource_src)

SET (demo_src Demo01.cpp ${demo_resources_src} ${demo_resources})

SOURCE_GROUP(\\ FILES ${demo_src})

ADD_EXECUTABLE(exeng.demo ${demo_src})

# Target properties
SET_PROPERTY(TARGET exeng.demo PROPERTY CXX_STANDARD 14)

IF (WIN32)
	SET_PROPERTY (TARGET exeng.demo PROPERTY RUNTIME_OUTPUT_DIRECTORY ${DEST_BIN_DIR})
ENDIF ()

# Target linking libraries
TARGET_LINK_LIBRARIES(exeng.demo exeng ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES})
