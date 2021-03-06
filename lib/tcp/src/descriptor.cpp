#include "descriptor.h"
#include <tcp_exception.h>
#include <utility>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>


namespace tcp
{

SocketDescriptor::SocketDescriptor(SocketDescriptor &&descriptor) noexcept
{
    *this = std::move(descriptor);
}

SocketDescriptor::SocketDescriptor(int fd) : fd_{fd} {}

SocketDescriptor& SocketDescriptor::operator=(SocketDescriptor &&descriptor) noexcept
{
    if (&descriptor != this)
    {
        close();
        fd_ = descriptor.fd_;
        descriptor.fd_ = -1;
    }

    return *this;
}

SocketDescriptor::~SocketDescriptor()
{
    close();
}

void SocketDescriptor::close()
{
    if (fd_ == -1)
        return;

    ::close(fd_);
    fd_ = -1;
}

int SocketDescriptor::getFd() const
{
    return fd_;
}

void SocketDescriptor::setFd(int fd)
{
    close();
    fd_ = fd;
}

void SocketDescriptor::setTimeout(unsigned msecs)
{
    timeval timeout{};

    timeout.tv_sec = msecs / 1000;
    timeout.tv_usec = (msecs % 1000) * 1000;

    if (setsockopt(fd_, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0
        || setsockopt(fd_, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
    {
        throw TcpException(std::string{"cannot set timeout"} + std::strerror(errno));
    }
}

void SocketDescriptor::setNonBlocking()
{
    int flags = fcntl(fd_, F_GETFL);
    if (flags < 0)
    {
        throw TcpException(std::string{"cannot get socket flags "} + std::strerror(errno));
    }

    if (fcntl(fd_, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        throw TcpException(std::string{"cannot make socket non-blocking"} + std::strerror(errno));
    }
}

} // namespace tcp