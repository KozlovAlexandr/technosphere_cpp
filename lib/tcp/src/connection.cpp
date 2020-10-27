#include "connection.h"
#include "tcp_exception.h"
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>

namespace tcp
{

Connection::Connection(const std::string& ipAddress, unsigned short port)
{
    connect(ipAddress, port);
}

Connection::Connection(int fd)
{
    socketDescriptor_.setFd(fd);
}

void Connection::connect(const std::string &ipAddress, unsigned short port)
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

    if (::connect(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    {
        throw TcpException("connection error");
    }

    socketDescriptor_ = std::move(newSocketDescriptor);
}

size_t Connection::write(const void* data, size_t len)
{
    ssize_t bytesWritten = ::write(socketDescriptor_.getFd(), data, len);
    if (bytesWritten < 0)
        throw TcpException("cannot write to socket descriptor");

    return bytesWritten;
}

size_t Connection::read(void *data, size_t len)
{
    ssize_t bytesRead = ::read(socketDescriptor_.getFd(), data, len);
    if (bytesRead < 0)
        throw TcpException("cannot read from socket descriptor");

    return bytesRead;
}

void Connection::readExact(void *data, size_t len)
{
    size_t bytesTotalRead = 0;

    while (bytesTotalRead != len)
    {
        size_t bytesRead = read(static_cast<char*>(data) + bytesTotalRead, len - bytesTotalRead);
        if (!bytesRead)
            throw TcpException("socket was closed");

        bytesTotalRead += bytesRead;
    }
}

void Connection::writeExact(const void *data, size_t len)
{
    size_t bytesWritten = 0;

    while (bytesWritten != len)
    {
        bytesWritten += write(static_cast<const char*>(data) + bytesWritten, len - bytesWritten);
    }
}

void Connection::close()
{
    socketDescriptor_.close();
}

void Connection::setTimeout(unsigned msecs)
{
    socketDescriptor_.setTimeout(msecs);
}

} // namespace tcp
