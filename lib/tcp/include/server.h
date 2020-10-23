#pragma once

#include <string>
#include <sys/socket.h>
#include "connection.h"

namespace tcp
{

class Server
{
public:
    Server() = default;
    Server(const std::string &ipAddress, unsigned port, int maxConnections = SOMAXCONN);

    Server(Server&& server) = default;
    Server &operator=(Server &&server) = default;

    void open(const std::string &ipAddress, unsigned short port, int maxConnections = SOMAXCONN);
    void setTimeout(time_t sec);
    void close();
    Connection accept();

private:

    SocketDescriptor socketDescriptor;
};

} // namespace tcp