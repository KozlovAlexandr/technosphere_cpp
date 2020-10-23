add_library(process STATIC src/process.cpp src/pipewrapper.cpp)
target_include_directories(process PUBLIC include)

add_executable(process_example example/example.cpp)
target_link_libraries(process_example process)