#include <iostream>
#include "server.h"
#include "connection.h"

int main()
{
    tcp::Server server("0.0.0.0", 8001);

    tcp::Connection conn = server.accept();
    server.close();

    conn.write("Hello, world!", sizeof("Hello, world"));
    conn.close();

    return 0;
}