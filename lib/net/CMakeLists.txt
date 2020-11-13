add_library(net STATIC src/epoll_wrapper.cpp src/buffered_connection.cpp src/service.cpp)
target_link_libraries(net tcp)
target_include_directories(net PUBLIC include)

add_executable(net_server example/net_server.cpp)
add_executable(net_client example/net_client.cpp)

target_link_libraries(net_server net)
target_link_libraries(net_client tcp pthread)