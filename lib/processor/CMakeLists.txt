add_library(processor STATIC src/process.cpp src/pipewrapper.cpp)
target_include_directories(processor PUBLIC include)

add_executable(example example/example.cpp)
target_link_libraries(example processor)