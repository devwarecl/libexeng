
set (target tetris)
set (sources 
    TetrisApp.hpp TetrisApp.cpp 
    PhongPipeline.hpp PhongPipeline.cpp 
)

source_group(\\ FILES ${sources})

add_executable(${target} ${sources})

set_property(TARGET ${target} PROPERTY CXX_STANDARD 14)

target_link_libraries(${target} xe xe.main)
