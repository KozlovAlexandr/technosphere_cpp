#include "net_exception.h"
#include "epoll_wrapper.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <cstring>

namespace net
{

EpollDescriptor::EpollDescriptor() : fd_{-1} {}

EpollDescriptor::~EpollDescriptor()
{
    close();
}

void EpollDescriptor::open()
{
    fd_ = epoll_create(1);
    if (fd_ < 0)
        throw NetException("cannot create epoll");
}

void EpollDescriptor::close()
{
    ::close(fd_);
    fd_ = -1;
}

void EpollDescriptor::add(int fd, uint32_t events)
{
    ::epoll_event event{};
    event.events = events;
    event.data.fd = fd;

    if (::epoll_ctl(fd_, EPOLL_CTL_ADD, fd, &event) < 0)
        throw NetException(std::string{"cannot add events_ to epoll "} + strerror(errno));
}

void EpollDescriptor::del(int fd)
{
    if (::epoll_ctl(fd_, EPOLL_CTL_DEL, fd, nullptr) < 0)
        throw NetException(std::string{"cannot delete descriptor from epoll "} + strerror(errno));
}

void EpollDescriptor::mod(int fd, uint32_t events)
{
    ::epoll_event event{};
    event.events = events;
    event.data.fd = fd;

    if (::epoll_ctl(fd_, EPOLL_CTL_MOD, fd, &event) < 0)
        throw NetException(std::string{"cannot mod events_ "} + std::strerror(errno));
}

std::vector<::epoll_event> EpollDescriptor::wait(int ms, int maxEvents)
{
    std::vector<::epoll_event> eventQueue(maxEvents);

    int eventsCount = ::epoll_wait(fd_, eventQueue.data(), eventQueue.size(), ms);
    if (eventsCount < 0)
    {
        if (errno == EINTR)
            throw TimeoutNetException("wait timeout error");

        throw NetException(std::string{"error in epoll_wait "} + strerror(errno));
    }

    eventQueue.resize(eventsCount);
    return eventQueue;
}

EpollDescriptor::EpollDescriptor(EpollDescriptor &&other) noexcept
{
    *this = std::move(other);
}

EpollDescriptor &EpollDescriptor::operator=(EpollDescriptor &&other) noexcept
{
    if (&other != this)
    {
        close();
        fd_ = other.fd_;
        other.fd_ = -1;
    }

    return *this;
}

} // namespace net