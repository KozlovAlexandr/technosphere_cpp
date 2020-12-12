#include "tcp_server.h"
#include "tcp_exception.h"
#include <arpa/inet.h>
#include <string>
#include <cstring>

namespace tcp
{

Server::Server(const std::string &ipAddress, unsigned short port, int maxConnections)
{
    open(ipAddress, port, maxConnections);
}

void Server::open(const std::string &ipAddress, unsigned short port, int maxConnections)
{
    int fd = ::socket(PF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        throw TcpException("cannot create a socket");
    }

    SocketDescriptor newSocketDescriptor(fd);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (::inet_aton(ipAddress.data(), &addr.sin_addr) == 0)
    {
        throw TcpException("cannot parse ip address");
    }

    int reuseAddrValue = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseAddrValue, sizeof(reuseAddrValue)) < 0)
    {
        throw TcpException("cannot set SO_REUSEADDR option");
    }

    if (::bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    {
        throw TcpException("cannot bind address");
    }

    if (::listen(fd, maxConnections) < 0)
    {
        throw TcpException("listen call error");
    }

    socketDescriptor_ = std::move(newSocketDescriptor);
}

void Server::close()
{
    socketDescriptor_.close();
}

Connection Server::accept()
{
    sockaddr_in clientAddress{};
    socklen_t addrSize = sizeof(clientAddress);

    int fd = ::accept(socketDescriptor_.getFd(), reinterpret_cast<sockaddr*>(&clientAddress), &addrSize);
    if (fd < 0)
    {
        throw TcpException("cannot accept connection");
    }

    return Connection(fd);
}

void Server::setTimeout(unsigned msecs)
{
    socketDescriptor_.setTimeout(msecs);
}

void Server::setNonBlocking()
{
    socketDescriptor_.setNonBlocking();
}

int Server::getFd() const
{
    return socketDescriptor_.getFd();
}

} // namespace tcp