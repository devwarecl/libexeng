
ADD_LIBRARY(xe.sg.scene_xml SHARED SceneLoaderXML.cpp)

TARGET_LINK_LIBRARIES (xe.sg.scene_xml xe ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES})

INSTALL (
	TARGETS xe.sg.scene_xml
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
)
