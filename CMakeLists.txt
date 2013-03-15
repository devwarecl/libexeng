
project (exeng)
project (test)
project (raytracer)

cmake_minimum_required(VERSION 2.6)

set (CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)
set (EXENG_VERSION_MAJOR 0)
set (EXENG_VERSION_MINOR 1)

## Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++0x") 
    #set(CMAKE_EXE_LINKER_FLAGS "-s")
endif()

add_subdirectory(src)

# TODO: Ver como ejecutar post 
# Pruebas unitarias
# enable_testing()
# add_test(exeng-test test)
