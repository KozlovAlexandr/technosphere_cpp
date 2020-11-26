#pragma once

#include "listener.h"
#include "server.h"

namespace net
{

class Service
{
public:
    Service() = default;
    Service(Service &&other) = default;
    Service(const Service &service) = delete;

    void setListener(IServiceListener *listener);
    void open(const std::string &ipAddress, unsigned short port, int maxConnections = SOMAXCONN);
    void close();

    [[noreturn]] void run();

private:
    std::vector<BufferedConnection> connections_;
    IServiceListener *listener_ = nullptr;
    EpollDescriptor epoll_;
    tcp::Server server_;
};

} // namespace net