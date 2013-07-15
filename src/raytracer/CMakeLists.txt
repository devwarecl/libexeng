set(CMAKE_CXX_FLAGS "-std=c++0x")

# Boost Configuration
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS system timer REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OpenGL_INCLUDE_DIRS})

include_directories( ${PROJECT_SOURCE_DIR}/src)
add_executable(raytracer OpenGLApp.cpp RayTracerApp.cpp SphereGeometry.cpp RayTracerAppPrivate.cpp 
                         samplers/Sampler.cpp samplers/JitteredSampler.cpp RayTracerMain.cpp)

target_link_libraries(raytracer exeng SDL ${OpenGL_LIBRARIES} ${Boost_LIBRARIES})

add_subdirectory(samplers)
