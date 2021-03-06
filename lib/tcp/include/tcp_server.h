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
    Server(const std::string &ipAddress, unsigned short port, int maxConnections = SOMAXCONN);

    Server(Server&& server) = default;
    Server &operator=(Server &&server) = default;

    void open(const std::string &ipAddress, unsigned short port, int maxConnections = SOMAXCONN);
    void setTimeout(unsigned msec);
    void close();
    Connection accept();
    void setNonBlocking();
    [[nodiscard]] int getFd() const;

private:
    SocketDescriptor socketDescriptor_;
};

} // namespace tcp