add_library(tcp STATIC src/connection.cpp src/tcp_server.cpp src/descriptor.cpp)
target_include_directories(tcp PUBLIC include)

add_executable(tcp_server_example example/tcp_server_example.cpp)
add_executable(tcp_client_example example/tcp_client_example.cpp)

target_link_libraries(tcp_server_example tcp)
target_link_libraries(tcp_client_example tcp)