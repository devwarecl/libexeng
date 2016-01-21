
SET (BaseFiles 
	TestMain.cpp 
    TestMath.cpp 
    TestScenegraph.cpp 
	TestMeshSubset.cpp 
	TestBuffer.cpp
)

SOURCE_GROUP (\\ FILES ${BaseFiles})

ADD_EXECUTABLE (xe.tests ${BaseFiles})

SET_PROPERTY (TARGET xe.tests PROPERTY CXX_STANDARD 14)

TARGET_LINK_LIBRARIES (xe.tests xe ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
