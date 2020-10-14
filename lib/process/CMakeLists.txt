add_library(process STATIC src/process.cpp src/pipewrapper.cpp)
target_include_directories(process PUBLIC include)

add_executable(example example/example.cpp)
target_link_libraries(example process)