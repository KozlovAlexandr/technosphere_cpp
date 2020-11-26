add_library(tcp STATIC src/connection.cpp src/server.cpp src/descriptor.cpp)
target_include_directories(tcp PUBLIC include)

add_executable(server_example example/server.cpp)
add_executable(client_example example/client.cpp)

target_link_libraries(server_example tcp)
target_link_libraries(client_example tcp)