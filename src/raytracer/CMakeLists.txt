if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

add_definitions(-DBOOST_ALL_DYN_LINK)

# Boost Configuration
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

find_package(SDL REQUIRED)
find_package(Boost COMPONENTS system timer REQUIRED)

include_directories(${SDL_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

link_directories(${Boost_LIBRARY_DIRS})

add_executable(raytracer OpenGLApp.cpp RayTracerApp.cpp SphereGeometry.cpp RayTracerAppPrivate.cpp 
                         samplers/Sampler.cpp samplers/JitteredSampler.cpp RayTracerMain.cpp)

target_link_libraries(raytracer exeng ${SDL_LIBRARY} ${Boost_LIBRARIES} )

add_subdirectory(samplers)
