#pragma once
#include <sys/epoll.h>
#include <vector>

namespace net
{

class EpollDescriptor
{
public:
    EpollDescriptor();
    EpollDescriptor(EpollDescriptor &&other) noexcept;
    EpollDescriptor &operator=(EpollDescriptor &&descriptor) noexcept ;
    EpollDescriptor(const EpollDescriptor &other) = delete;
    ~EpollDescriptor();

    void close();
    void add(int fd, uint32_t events);
    void mod(int fd, uint32_t events);
    void del(int fd);
    void open();
    std::vector<::epoll_event> wait(int ms = -1, int maxEvents = 1024);

private:
    int fd_ = -1;
};

} // namespace net