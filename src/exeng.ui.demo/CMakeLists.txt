include_directories( ${PROJECT_SOURCE_DIR}/src )

IF (WIN32)
  add_executable (exeng.ui.demo WIN32 Main.cpp)
ELSE ()
  add_executable (exeng.ui.demo Main.cpp)
ENDIF(WIN32)

target_link_libraries (exeng.ui.demo exeng exeng.main)
