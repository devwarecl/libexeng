
include_directories(${PROJECT_SOURCE_DIR}/src)

SET (source_files Main.hpp Main.cpp)

SOURCE_GROUP(\\ FILES ${source_files})

add_library(exeng.main STATIC ${source_files})
