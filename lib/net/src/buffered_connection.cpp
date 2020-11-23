#include "buffered_connection.h"

namespace net
{

BufferedConnection::BufferedConnection(tcp::Connection &&connection, EpollDescriptor &epollDescriptor, uint32_t events) :
        epollDescriptor_(epollDescriptor),
        connection_(std::move(connection)),
        events_(events)
{
    epollDescriptor_.get().add(connection_.getFd(), events_);
}

void BufferedConnection::subscribeRead()
{
    events_ |= EPOLLIN;
    epollDescriptor_.get().mod(connection_.getFd(), events_);
}

void BufferedConnection::subscribeWrite()
{
    events_ |= EPOLLOUT;
    epollDescriptor_.get().mod(connection_.getFd(), events_);
}

void BufferedConnection::unsubscribeRead()
{
    events_ &= ~EPOLLIN;
    epollDescriptor_.get().mod(connection_.getFd(), events_);
}

void BufferedConnection::unsubscribeWrite()
{
    events_ &= ~EPOLLOUT;
    epollDescriptor_.get().mod(connection_.getFd(), events_);
}

void BufferedConnection::close()
{
    connection_.close();
}

size_t BufferedConnection::writeFromBuf()
{
    size_t writtenBytes = connection_.write(writeBuf_.data(), writeBuf_.size());
    writeBuf_.erase(writeBuf_.begin(), writeBuf_.begin() + writtenBytes);

    return writtenBytes;
}

size_t BufferedConnection::readToBuf()
{
    size_t oldSize = readBuf_.size();
    readBuf_.resize(MAX_READ_BUF_CAPACITY);

    size_t bytesRead = connection_.read(readBuf_.data() + oldSize, MAX_READ_BUF_CAPACITY - oldSize);
    readBuf_.resize(oldSize + bytesRead);

    return bytesRead;
}

int BufferedConnection::getFd() const
{
    return connection_.getFd();
}

std::string &BufferedConnection::readBuf()
{
    return readBuf_;
}

std::string &BufferedConnection::writeBuf()
{
    return writeBuf_;
}

void BufferedConnection::setTimeout(unsigned int msecs)
{
    connection_.setTimeout(msecs);
}

void BufferedConnection::setNonBlocking()
{
    connection_.setNonBlocking();
}

} // namespace net