
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

add_definitions(-DBOOST_ALL_DYN_LINK -DSANDBOX_ROOT_FOLDER="${PROJECT_SOURCE_DIR}/src/exeng.sandbox/")

# Boost Configuration
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

find_package(OpenCL REQUIRED)
find_package(Boost COMPONENTS system timer REQUIRED)
find_package(glfw REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${OPENCL_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIRS})
link_directories(${GLFW_LIBRARY_DIR})

# Grouping
file (GLOB RES_FILES *.cl *.glsl)

set (SandboxFiles
	Main.cpp gl_core_3_3.h gl_core_3_3.c
)

source_group(\\ FILES ${SandboxFiles})

add_executable(exeng.sandbox ${SandboxFiles} ${RES_FILES})

# 
target_link_libraries(exeng.sandbox exeng ${Boost_LIBRARIES} ${GLFW_LIBRARY} ${OPENCL_LIBRARIES}  ${OPENGL_LIBRARIES})
