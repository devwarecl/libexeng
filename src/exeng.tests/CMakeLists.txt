
include_directories( ${PROJECT_SOURCE_DIR}/src)

# FIND_PACKAGE(UnitTestPP)

SET (BaseFiles 
	TestMain.cpp 
    TestMath.cpp 
    TestScenegraph.cpp  
)

SOURCE_GROUP(\\ FILES ${BaseFiles})

add_executable(exeng.tests ${BaseFiles})
target_link_libraries(exeng.tests exeng UnitTest++)

# ENDIF (UnitTestPP_FOUND)


