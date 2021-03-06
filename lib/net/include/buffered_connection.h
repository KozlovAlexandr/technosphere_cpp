#pragma once

#include "epoll_wrapper.h"
#include "connection.h"

namespace net
{

class BufferedConnection
{
public:
    /// epollDescriptor must must be valid for the lifetime of the BufferedConnection
    BufferedConnection(tcp::Connection &&conn, EpollDescriptor &epollDescriptor, uint32_t events = EPOLLRDHUP);
    BufferedConnection(BufferedConnection&&) noexcept = default;
    BufferedConnection& operator=(BufferedConnection&&) noexcept = default;
    BufferedConnection() = delete;
    BufferedConnection(const BufferedConnection&) = delete;
    ~BufferedConnection() = default;

    void reactivate();
    void subscribeRead();
    void subscribeWrite();
    void subReadUnsubWrite();
    void subReadSubClose();
    void subWriteUnsubRead();

    void unsubscribeRead();
    void unsubscribeWrite();

    void close();

    size_t writeFromBuf();
    size_t readToBuf();

    std::string& readBuf();
    std::string& writeBuf();

    [[nodiscard]] int getFd() const;

    void setTimeout(unsigned msecs);
    void setNonBlocking();

protected:

    tcp::Connection connection_;
    EpollDescriptor *epollDescriptor_;
    uint32_t events_;

private:

    std::string readBuf_;
    std::string writeBuf_;
};

} // namespace net