
add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_TEST_DYN_LINK)

set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories( ${PROJECT_SOURCE_DIR}/src)
include_directories( ${Boost_INCLUDE_DIRS} )

set (BaseFiles 
	TestMain.cpp 
    TestMath.cpp 
    TestScenegraph.cpp  
)

source_group (\\ FILES ${BaseFiles})

add_executable(exeng.tests ${BaseFiles})
target_link_libraries(exeng.tests exeng  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
