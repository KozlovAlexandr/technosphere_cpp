add_library(logger STATIC   src/BaseLogger.cpp
                            src/StderrLogger.cpp
                            src/StdoutLogger.cpp
                            src/FileLogger.cpp
                            src/Logger.cpp)

target_include_directories(logger PUBLIC include)

add_subdirectory(example)
