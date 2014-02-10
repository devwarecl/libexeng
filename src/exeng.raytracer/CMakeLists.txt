if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

add_definitions(-DBOOST_ALL_DYN_LINK)

# Boost Configuration
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS system timer REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

link_directories(${Boost_LIBRARY_DIRS})

# Grouping
set (BaseFiles
	RayTracerApp.hpp                RayTracerApp.cpp 
    RayTracerSceneRenderer.hpp      RayTracerSceneRenderer.cpp 
)

set ( Tracers
	tracers/Tracer.hpp              tracers/Tracer.cpp 
    tracers/SoftwareTracer.hpp      tracers/SoftwareTracer.cpp 
    tracers/HardwareTracer.hpp      tracers/HardwareTracer.cpp 
)

set ( Samplers
	samplers/Sampler.hpp            samplers/Sampler.cpp 
    samplers/JitteredSampler.hpp    samplers/JitteredSampler.cpp 
)

if (WIN32)
	add_executable(exeng.raytracer WIN32 ${BaseFiles} ${Tracers} ${Samplers} )
else ()
	add_executable(exeng.raytracer		 ${BaseFiles} ${Tracers} ${Samplers} )
endif(WIN32)

target_link_libraries(exeng.raytracer exeng exeng.main ${Boost_LIBRARIES} OpenCL )

source_group(root		FILES ${BaseFiles})
source_group(tracers	FILES ${Tracers})
source_group(samplers	FILES ${Samplers})

add_subdirectory(samplers)
add_subdirectory(tracers)
