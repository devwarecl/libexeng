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

add_executable(raytracer 
    RayTracer.hpp					RayTracer.cpp 
    RayTracerApp.hpp				RayTracerApp.cpp 
    SphereGeometry.hpp				SphereGeometry.cpp 
    samplers/Sampler.hpp			samplers/Sampler.cpp 
    samplers/JitteredSampler.hpp	samplers/JitteredSampler.cpp 
)

target_link_libraries(raytracer exeng ${Boost_LIBRARIES} OpenCL )

add_subdirectory(samplers)
