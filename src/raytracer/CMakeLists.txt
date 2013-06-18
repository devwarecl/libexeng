set(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories( ${PROJECT_SOURCE_DIR}/src)
add_executable(raytracer 
OpenGLApp.cpp RayTracerApp.cpp SphereGeometry.cpp 
RayTracerAppPrivate.cpp samplers/Sampler.cpp samplers/JitteredSampler.cpp 
RayTracerMain.cpp)
target_link_libraries(raytracer exeng SDL GL GLU boost_system boost_timer)




add_subdirectory(samplers)