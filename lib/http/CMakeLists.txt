add_library(http STATIC src/http_server.cpp src/http_connection.cpp src/http.cpp)
target_link_libraries(http tcp)
target_link_libraries(http net)
target_link_libraries(http logger)
target_include_directories(http PUBLIC include)

add_executable(http_server example/http_server.cpp)
add_executable(http_client example/http_client.cpp)

target_link_libraries(http_server http pthread)
target_link_libraries(http_client http pthread)