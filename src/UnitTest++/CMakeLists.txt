
# option(UTPP_USE_PLUS_SIGN Set this to OFF is you with to use '-cpp' instead of '++' in libinclude paths ON)

# get the main sources
file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")
source_group(\\ FILES ${headers_} ${sources_})

# get platform specific sources
if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    file(GLOB platformHeaders_ ${platformDir_}"Win32/*.h")
	file(GLOB platformHeaders_ ${platformDir_}"Win32/*.cpp")
else()
    file(GLOB platformHeaders_ ${platformDir_}"Posix/*.h")
	file(GLOB platformHeaders_ ${platformDir_}"Posix/*.cpp")
endif(WIN32)

# file(GLOB platformHeaders_ ${platformDir_}"Win32/*.h")
# file(GLOB platformHeaders_ ${platformDir_}"Win32/*.cpp")
# file(GLOB platformSources_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} UnitTest++${platformDir_}.cpp)
source_group(\\platform FILES ${platformHeaders_} ${platformSources_})

# create the lib
add_library(UnitTest++ STATIC ${headers_} ${sources_} ${platformHeaders_} ${platformSources_})

# SET_TARGET_PROPERTIES(UnitTest++ PROPERTIES LINKER_LANGUAGE C++)
# if(${UTPP_USE_PLUS_SIGN})
#	set_target_properties(UnitTest++ PROPERTIES OUTPUT_NAME UnitTest++)
#endif()
