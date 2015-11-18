
SET (EXENG_PREFIX "E:/DevTools/Libraries/libexeng")

SET (exeng_INCLUDE_DIRS "${EXENG_PREFIX}/include/")

IF (WIN32 AND NOT CYGWIN)
	SET (exeng_LIBRARY 		"${EXENG_PREFIX}/lib/exeng.lib")
ELSE ()
	SET (exeng_LIBRARY 		"${EXENG_PREFIX}/lib/libexeng.so")
ENDIF()
