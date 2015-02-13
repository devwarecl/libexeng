project (libexeng)

cmake_minimum_required(VERSION 2.6)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set (CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)
set (EXENG_VERSION_MAJOR 0)
set (EXENG_VERSION_MINOR 2)

add_definitions(-DEXENG_DYNAMIC)

## Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++1y -Wall")
endif()

add_subdirectory(src)
add_subdirectory(plugins)

if (WIN32)
    set_property(TARGET exeng.raytracer PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
    set_property(TARGET exeng.tests PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
    set_property(TARGET exeng PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
    set_property(TARGET exeng.graphics.gl3 PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
	set_property(TARGET exeng.ui.demo PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
endif (WIN32)

# enable_testing()
# add_test(exeng-test test)
