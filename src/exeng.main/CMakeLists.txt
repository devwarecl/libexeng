
SET (source_files Main.hpp Main.cpp)

SOURCE_GROUP (\\ FILES ${source_files})

ADD_LIBRARY (exeng.main STATIC ${source_files})
