#include "server.h"
#include "tcp_exception.h"
#include <arpa/inet.h>
#include <string>
#include <cstring>

namespace tcp
{

Server::Server(const std::string &ipAddress, unsigned int port, int maxConnections)
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
        throw TcpException(strerror(errno));
    }

    if (::bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    {
        throw TcpException(strerror(errno));
    }

    if (::listen(fd, maxConnections) < 0)
    {
        throw TcpException(strerror(errno));
    }

    socketDescriptor.setFd(fd);
}

void Server::close()
{
    socketDescriptor.close();
}

Connection Server::accept()
{
    sockaddr_in clientAddress{};
    socklen_t addrSize = sizeof(clientAddress);

    int fd = ::accept(socketDescriptor.getFd(), reinterpret_cast<sockaddr*>(&clientAddress), &addrSize);
    if (fd < 0)
    {
        throw TcpException("cannot accept connection");
    }

    return Connection(fd);
}

void Server::setTimeout(time_t secs)
{
    socketDescriptor.setTimeout(secs);
}

} // namespace tcp