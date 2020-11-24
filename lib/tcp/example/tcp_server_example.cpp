#include <iostream>
#include "tcp_server.h"
#include "connection.h"

int main()
{
    tcp::Server server("0.0.0.0", 8001);

    tcp::Connection conn = server.accept();
    server.close();

    std::string message = "Hello, world!";
    conn.write(message.data(), message.size());
    conn.close();

    return 0;
}