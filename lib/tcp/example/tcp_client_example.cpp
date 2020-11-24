#include <iostream>
#include "tcp_server.h"
#include "connection.h"

int main()
{
    tcp::Connection conn("127.0.0.1", 8001);

    std::string s;
    s.resize(sizeof("Hello, world"));

    conn.read(s.data(), s.size());
    conn.close();

    std::cout << s << std::endl;

    return 0;
}