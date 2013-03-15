
include_directories( ${PROJECT_SOURCE_DIR}/src)

add_executable(test 
    Main.cpp 
    TestMath.cpp 
    TestScenegraph.cpp  
)

target_link_libraries(test exeng unittest++)