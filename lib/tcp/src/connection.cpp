#include "connection.h"
#include "tcp_exception.h"
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>

namespace tcp
{

Connection::Connection(const std::string& ipAddress, unsigned port)
{
    connect(ipAddress, port);
}

Connection::Connection(int fd)
{
    socketDescriptor.close();
    socketDescriptor.setFd(fd);
}

void Connection::connect(const std::string &ipAddress, unsigned short port)
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

    if (::connect(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    {
        throw TcpException("connection error");
    }

    socketDescriptor.setFd(fd);
}

size_t Connection::write(const void* data, size_t len)
{
    ssize_t bytesWritten = ::write(socketDescriptor.getFd(), data, len);
    if (bytesWritten < 0)
        throw TcpException(strerror(errno));

    return bytesWritten;
}

size_t Connection::read(void *data, size_t len)
{
    ssize_t bytesRead = ::read(socketDescriptor.getFd(), data, len);
    if (bytesRead < 0)
        throw TcpException(strerror(errno));

    return bytesRead;
}

void Connection::readExact(void *data, size_t len)
{
    size_t bytesTotalRead = 0;

    while (bytesTotalRead != len)
    {
        size_t bytesRead = read(static_cast<char*>(data) + bytesTotalRead, len - bytesTotalRead);
        if (!bytesRead)
            throw TcpException("Socket was closed");

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
    socketDescriptor.close();
}

void Connection::setTimeout(time_t secs)
{
    socketDescriptor.setTimeout(secs);
}

} // namespace tcp
