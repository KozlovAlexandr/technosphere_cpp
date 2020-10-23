#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace tcp
{

class SocketDescriptor
{
public:
    SocketDescriptor() = default;
    explicit SocketDescriptor(int fd);
    SocketDescriptor(SocketDescriptor &&descriptor) noexcept;
    SocketDescriptor &operator=(SocketDescriptor &&descriptor) noexcept ;

    ~SocketDescriptor();

    [[nodiscard]] int getFd() const;
    void setFd(int fd);
    void close();

    void setTimeout(time_t secs);
private:
    int fd_ = -1;
};

} // namespace tcp