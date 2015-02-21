
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS filesystem REQUIRED)
add_definitions(-DBOOST_ALL_DYN_LINK)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${Boost_LIBRARY_DIRS})

add_executable(exeng.demo Demo01.cpp)
target_link_libraries(exeng.demo exeng ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
