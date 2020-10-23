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

void SocketDescriptor::setTimeout(time_t secs)
{
    timeval timeout{secs, 0};
    if (setsockopt(fd_, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0
        || setsockopt(fd_, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
    {
        throw TcpException(strerror(errno));
    }
}

} // namespace tcp