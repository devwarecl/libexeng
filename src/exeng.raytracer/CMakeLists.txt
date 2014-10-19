if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

add_definitions(-DBOOST_ALL_DYN_LINK -DRAYTRACER_ROOT_FOLDER="${PROJECT_SOURCE_DIR}/src/exeng.raytracer/")

# Boost Configuration
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)
find_package(Boost COMPONENTS system timer REQUIRED)
find_package(glfw REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${OPENCL_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIRS})
link_directories(${GLFW_LIBRARY_DIR})
link_directories(${OpenGL_LIBRARY_DIR})

# Grouping
set (BaseFiles
	RayTracerApp.hpp                RayTracerApp.cpp 
    RayTracerSceneRenderer.hpp      RayTracerSceneRenderer.cpp 
    FpsCounter.hpp                  FpsCounter.cpp 
    SceneLoader.hpp                 SceneLoader.cpp 
)

set (Kernels
	kernels/TraceRay.cl
	kernels/Common.cl
	kernels/ComputeSynthesisData.cl
	kernels/GenerateRays.cl
	kernels/SynthetizeImage.cl
)

set ( Tracers
	tracers/Tracer.hpp              tracers/Tracer.cpp 
    tracers/SoftwareTracer.hpp      tracers/SoftwareTracer.cpp 
    tracers/HardwareTracer.hpp      tracers/HardwareTracer.cpp 
	tracers/MultiHardwareTracer.hpp	tracers/MultiHardwareTracer.cpp 
)

set ( Samplers
	samplers/Sampler.hpp            samplers/Sampler.cpp 
    samplers/JitteredSampler.hpp    samplers/JitteredSampler.cpp 
)

add_executable(exeng.raytracer WIN32 ${BaseFiles} ${Tracers} ${Samplers} ${Kernels} )

target_link_libraries(exeng.raytracer exeng exeng.main ${Boost_LIBRARIES} ${OPENCL_LIBRARIES} ${OPENGL_LIBRARIES})

source_group(\\			FILES ${BaseFiles})
source_group(tracers	FILES ${Tracers})
source_group(samplers	FILES ${Samplers})
source_group(kernels	FILES ${Kernels})

add_subdirectory(samplers)
add_subdirectory(tracers)
