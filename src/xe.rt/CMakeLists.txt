
find_package(OpenGL REQUIRED)
find_package(OpenCL)
find_package(glfw3 REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
  find_package(Threads REQUIRED)
endif()

include_directories(${GLFW3_INCLUDE_DIR})
include_directories(${OPENCL_INCLUDE_DIRS})

add_definitions(-D__CL_ENABLE_EXCEPTIONS)
add_definitions(-DCL_USE_DEPRECATED_OPENCL_1_1_APIS)

link_directories(${GLFW3_LIBRARY_DIR})
link_directories(${OpenGL_LIBRARY_DIR})

# Grouping
set (BaseFiles
	RayTracerApp.hpp                RayTracerApp.cpp 
    SceneLoader.hpp                 SceneLoader.cpp 
    
    Sampler.hpp                     Sampler.cpp 
    JitteredSampler.hpp             JitteredSampler.cpp 
    
    HardwareRenderer.hpp			HardwareRenderer.cpp
	HardwareRendererPrivate.hpp     HardwareRendererPrivate.cpp
	SoftwareRenderer.hpp			SoftwareRenderer.cpp
)

ADD_EXECUTABLE (xe.rt ${BaseFiles})

SET_PROPERTY (TARGET xe.rt PROPERTY CXX_STANDARD 14)
IF (WIN32)
    SET_PROPERTY(TARGET xe.rt PROPERTY RUNTIME_OUTPUT_DIRECTORY ${DEST_BIN_DIR})
ENDIF ()

TARGET_LINK_LIBRARIES(xe.rt xe xe.main ${OPENGL_LIBRARIES} ${OPENCL_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

SOURCE_GROUP (\\ FILES ${BaseFiles})
