
cmake_minimum_required (VERSION 3.0)

project (libexeng)

# Engine options
option (XE_GFX_GL "Enable OpenGL graphics driver" OFF)
option (XE_GFX_D3D "Enable Direct3D graphics driver" OFF)
option (XE_GFX_FI "Enable FreeImage-based image loader implementation" OFF)
option (XE_GFX_LWO "Enable mesh loading from LWO files" OFF)
option (XE_SG_XML "Enable scene loading from XML files" OFF)
option (XE_CM_CL "Enable OpenCL computing module" OFF)
option (XE_GFX_ASSIMP "Enable Assimp mesh loader plugin" OFF)

option (XE_RT "Enable scene rendering trough Ray Tracing" OFF)
option (XE_TESTING "Enable unit testings" OFF)

option (XE_EXAMPLES "Build examples" OFF)

option (XE_MINIGAMES "Build minigames examples" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_include_directories_PROJECT_BEFORE ON)

# Engine version
set(XE_VERSION_MAJOR    0)
set(XE_VERSION_MINOR    1)
set(XE_VERSION_REVISION 1)
set(XE_VERSION_BUILD    0)

add_definitions(-DXE_VERSION_MAJOR=${XE_VERSION_MAJOR})
add_definitions(-DXE_VERSION_MINOR=${XE_VERSION_MINOR})
add_definitions(-DXE_VERSION_REVISION=${XE_VERSION_REVISION})
add_definitions(-DXE_VERSION_BUILD=${XE_VERSION_BUILD})

# Enable dynamic library generation
add_definitions (-DEXENG_DYNAMIC)

# Prepropressor for Visual C++
add_definitions (-D_CRT_SECURE_NO_WARNINGS)	
add_definitions (-D_SCL_SECURE_NO_WARNINGS)

# Boost.
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

add_definitions (-DBOOST_ALL_DYN_LINK)
add_definitions (-DBOOST_ALL_NO_LIB)
add_definitions (-DBOOST_TEST_DYN_LINK)

find_package (Boost 
	COMPONENTS 
		filesystem 
		system 
		unit_test_framework 
		timer 
		log 
		thread 
	REQUIRED
)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# libxml2
find_package(libxml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})
include_directories(${LIBXML2_INCLUDE_DIRS})

# Additional import libraries for unix
set(UNIX_LIBRARIES "")

if(UNIX AND NOT APPLE)
	set(UNIX_LIBRARIES dl rt)	
endif()

# 
include_directories(${PROJECT_SOURCE_DIR}/src)

# 
add_subdirectory (src/xe)
add_subdirectory (src/xe.demo)
add_subdirectory (src/xe.main)
add_subdirectory (src/xmlpp)

if(XE_MINIGAMES)
    add_subdirectory (minigames/tetris)
endif()

if(XE_TESTING)
	add_subdirectory (src/xe.tests)
endif()

if(XE_RT)
    add_subdirectory (src/xe.rt)
	add_subdirectory (src/xe.sg.sw)
endif()

# Add example programs
if(XE_EXAMPLES)
	add_subdirectory(examples/scene)
	add_subdirectory(examples/triangle)
	add_subdirectory(examples/texture)
	add_subdirectory(examples/simplemesh)
	add_subdirectory(examples/geogen)
	add_subdirectory(examples/compute)
	add_subdirectory(examples/computeinterop)
	add_subdirectory(examples/meshload)
endif()

# Engine plugins
if(XE_GFX_GL)
	add_subdirectory (plugins/xe.gfx.gl)
endif()

if(XE_SG_XML)
	add_subdirectory (plugins/xe.sg.scene_xml)
endif()

if(XE_GFX_FI)
	add_subdirectory (plugins/xe.gfx.fi)
endif()

if(XE_GFX_LWO)
	add_subdirectory (plugins/xe.gfx.lwo)
endif()

if(XE_CM_CL)
	add_subdirectory (plugins/xe.cm.cl)
endif()

if(XE_GFX_ASSIMP)
	add_subdirectory (plugins/xe.gfx.assimp)
endif()
