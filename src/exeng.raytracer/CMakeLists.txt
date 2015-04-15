
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

add_definitions(-DBOOST_ALL_DYN_LINK -DRAYTRACER_ROOT_FOLDER="${PROJECT_SOURCE_DIR}/src/exeng.raytracer/")

# Boost Configuration
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)
find_package(Boost COMPONENTS system timer log thread REQUIRED)
find_package(glfw3 REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
  find_package(Threads REQUIRED)
endif()

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${GLFW3_INCLUDE_DIR})
include_directories(${OPENCL_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIRS})
link_directories(${GLFW3_LIBRARY_DIR})
link_directories(${OpenGL_LIBRARY_DIR})

# Grouping
set (BaseFiles
	RayTracerApp.hpp                RayTracerApp.cpp 
    RayTracerSceneRenderer.hpp      RayTracerSceneRenderer.cpp 
    SceneLoader.hpp                 SceneLoader.cpp 
)

set (Kernels
	kernels/TraceRay.cl
	kernels/MultiHardwareTracer.cl
)

set (Tracers
	tracers/Tracer.hpp              tracers/Tracer.cpp 
    tracers/SoftwareTracer.hpp      tracers/SoftwareTracer.cpp 
    tracers/HardwareTracer.hpp      tracers/HardwareTracer.cpp 
	tracers/MultiHardwareTracer.hpp	tracers/MultiHardwareTracer.cpp 
	
	tracers/TracerFactory.hpp		tracers/TracerFactory.cpp 
	tracers/TracerCreator.hpp		tracers/TracerCreator.cpp 
)

set (Samplers
	samplers/Sampler.hpp            samplers/Sampler.cpp 
    samplers/JitteredSampler.hpp    samplers/JitteredSampler.cpp 
)

set (Loaders
	loaders/LwoMeshLoader.hpp		loaders/LwoMeshLoader.cpp
)

add_executable(exeng.raytracer ${BaseFiles} ${Tracers} ${Samplers} ${Kernels} ${Loaders})

target_link_libraries(exeng.raytracer exeng exeng.main ${OPENGL_LIBRARIES} ${OPENCL_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

source_group(\\			FILES ${BaseFiles})
source_group(tracers	FILES ${Tracers})
source_group(samplers	FILES ${Samplers})
source_group(kernels	FILES ${Kernels})
source_group(loaders	FILES ${Loaders})
