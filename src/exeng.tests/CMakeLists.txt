
include_directories( ${PROJECT_SOURCE_DIR}/src)

add_executable(exeng.tests
    TestMain.cpp 
    TestMath.cpp 
    TestScenegraph.cpp  
)

# target_link_libraries(test exeng unittest++)
