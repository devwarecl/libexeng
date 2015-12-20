
SET (BaseFiles 
	TestMain.cpp 
    TestMath.cpp 
    TestScenegraph.cpp  
)

SOURCE_GROUP (\\ FILES ${BaseFiles})

ADD_EXECUTABLE (xe.tests ${BaseFiles})

SET_PROPERTY (TARGET xe.tests PROPERTY CXX_STANDARD 14)
IF (WIN32)
	SET_PROPERTY (TARGET xe.tests PROPERTY RUNTIME_OUTPUT_DIRECTORY ${DEST_BIN_DIR})
ENDIF ()

TARGET_LINK_LIBRARIES (xe.tests xe ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
