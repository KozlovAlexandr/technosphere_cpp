#pragma once

#include "epoll_wrapper.h"
#include "connection.h"

namespace net
{

class BufferedConnection
{
public:
    /// epollDescriptor must must be valid for the lifetime of the BufferedConnection
    BufferedConnection(tcp::Connection &&conn, EpollDescriptor &epollDescriptor);
    BufferedConnection(BufferedConnection&&) noexcept = default;
    BufferedConnection& operator=(BufferedConnection&&) noexcept = default;
    BufferedConnection() = delete;
    BufferedConnection(const BufferedConnection&) = delete;
    ~BufferedConnection() = default;

    void subscribeRead();
    void subscribeWrite();
    void unsubscribeRead();
    void unsubscribeWrite();

    void close();

    size_t writeFromBuf();
    size_t readToBuf();

    std::string& readBuf();
    std::string& writeBuf();

    [[nodiscard]] int getFd() const;

private:
    tcp::Connection connection_;
    EpollDescriptor *epollDescriptor_;
    std::string readBuf_;
    std::string writeBuf_;
    uint32_t events_;
};

} // namespace net