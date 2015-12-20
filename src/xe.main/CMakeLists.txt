
SET (source_files Main.hpp Main.cpp)

SOURCE_GROUP (\\ FILES ${source_files})

ADD_LIBRARY (xe.main STATIC ${source_files})
