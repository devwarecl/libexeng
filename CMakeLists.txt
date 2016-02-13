
PROJECT (libexeng)

CMAKE_MINIMUM_REQUIRED (VERSION 3.0)

# Engine options
OPTION (XE_GFX_GL3 "Enable OpenGL 3 graphics driver" OFF)
OPTION (XE_GFX_D3D "Enable Direct3D graphics driver" OFF)
OPTION (XE_GFX_FI "Enable FreeImage-based image loader implementation" OFF)
OPTION (XE_GFX_LWO "Enable mesh loading from LWO files" OFF)
OPTION (XE_SG_XML "Enable scene loading from XML files" OFF)
OPTION (XE_CM_CL "Enable OpenCL computing module" OFF)
OPTION (XE_GFX_ASSIMP "Enable Assimp mesh loader plugin" OFF)

OPTION (XE_RT "Enable scene rendering trough Ray Tracing" OFF)
OPTION (XE_TESTING "Enable unit testings" OFF)

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
SET (CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)

SET (XE_VERSION_MAJOR		0)
SET (XE_VERSION_MINOR		1)
SET (XE_VERSION_REVISION	1)
SET (DEST_BIN_DIR ${PROJECT_BINARY_DIR}/bin)

# Enable dynamic library generation
ADD_DEFINITIONS (-DEXENG_DYNAMIC)

# Prepropressor for Visual C++
ADD_DEFINITIONS (-D_CRT_SECURE_NO_WARNINGS)	
ADD_DEFINITIONS (-D_SCL_SECURE_NO_WARNINGS)

# Boost.
SET (Boost_USE_STATIC_LIBS OFF)
SET (Boost_USE_MULTITHREADED ON)
SET (Boost_USE_STATIC_RUNTIME OFF)

ADD_DEFINITIONS (-DBOOST_ALL_DYN_LINK)
ADD_DEFINITIONS (-DBOOST_ALL_NO_LIB)
ADD_DEFINITIONS (-DBOOST_TEST_DYN_LINK)

FIND_PACKAGE (Boost 
	COMPONENTS 
		filesystem 
		system 
		unit_test_framework 
		timer 
		log 
		thread 
	REQUIRED
)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# libxml2
FIND_PACKAGE(libxml2 REQUIRED)
INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIRS})

# Additional import libraries for unix
SET (UNIX_LIBRARIES "")

IF(UNIX AND NOT APPLE)
	SET (UNIX_LIBRARIES dl rt)	
ENDIF()

# 
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

# 
ADD_SUBDIRECTORY (src/xe)
ADD_SUBDIRECTORY (src/xe.demo)
ADD_SUBDIRECTORY (src/xe.main)
ADD_SUBDIRECTORY (src/xe.sandbox)
ADD_SUBDIRECTORY (src/xmlpp)

IF (XE_TESTING)
	ADD_SUBDIRECTORY (src/xe.tests)
ENDIF ()

IF (XE_RT)
    ADD_SUBDIRECTORY (src/xe.rt)
ENDIF ()

# Add example programs
add_subdirectory(examples/triangle)
add_subdirectory(examples/texture)

# Engine plugins
IF(XE_GFX_GL3)
	ADD_SUBDIRECTORY (plugins/xe.gfx.gl3)
ENDIF ()

IF(XE_SG_XML)
	ADD_SUBDIRECTORY (plugins/xe.sg.scene_xml)
ENDIF()

IF(XE_GFX_FI)
	ADD_SUBDIRECTORY (plugins/xe.gfx.fi)
ENDIF()

IF(XE_GFX_LWO)
	ADD_SUBDIRECTORY (plugins/xe.gfx.lwo)
ENDIF()

IF(XE_CM_CL)
	ADD_SUBDIRECTORY (plugins/xe.cm.cl)
ENDIF()

IF(XE_GFX_ASSIMP)
	ADD_SUBDIRECTORY (plugins/xe.gfx.assimp)
ENDIF()
