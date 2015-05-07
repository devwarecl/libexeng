
SET (Boost_USE_STATIC_LIBS OFF)
SET (Boost_USE_MULTITHREADED ON)
SET (Boost_USE_STATIC_RUNTIME OFF)

FIND_PACKAGE(libxml2 REQUIRED)
FIND_PACKAGE(Boost COMPONENTS filesystem REQUIRED)
ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

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
# SET (demo_src Demo01.cpp ${demo_resources_src})

SOURCE_GROUP(\\ FILES ${demo_src})

ADD_EXECUTABLE(exeng.demo ${demo_src})
TARGET_LINK_LIBRARIES(exeng.demo exeng ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES})
