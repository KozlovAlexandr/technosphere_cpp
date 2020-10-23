#include <iostream>
#include "server.h"
#include "connection.h"

int main()
{
    tcp::Connection conn("127.0.0.1", 8001);

    char s[sizeof("Hello, world!")];

    conn.read(s, sizeof("Hello, world!"));
    conn.close();

    std::cout << s << std::endl;

    return 0;
}