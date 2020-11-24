#include "service.h"
#include "net_exception.h"
#include <algorithm>
#include <iostream>

namespace net
{

void Service::setListener(IServiceListener *listener)
{
    listener_ = listener;
}

void Service::open(const std::string &ipAddress, unsigned short port, int maxConnections)
{
    tcp::Server tmpServer(ipAddress, port, maxConnections);
    tmpServer.setNonBlocking();

    net::EpollDescriptor tmpEpoll;
    tmpEpoll.open();
    tmpEpoll.add(tmpServer.getFd(), EPOLLIN);

    server_ = std::move(tmpServer);
    epoll_ = std::move(tmpEpoll);
}

void Service::close()
{
    server_.close();
}

[[noreturn]] void Service::run()
{
    while (true)
    {
        std::vector<::epoll_event> eventQueue = epoll_.wait();
        for (const epoll_event &event : eventQueue)
        {
            std::cout << connections_.size() << " connections left" << std::endl;
            if (event.data.fd == server_.getFd())
            {
                BufferedConnection newConn{server_.accept(), epoll_};

                connections_.push_back(std::move(newConn));
                listener_->onNewConnection(connections_.back());
                continue;
            }

            auto connIt = std::find_if(connections_.begin(), connections_.end(),
                                       [fd = event.data.fd](const BufferedConnection &conn) {
                                           return conn.getFd() == fd;
                                       });
            BufferedConnection &conn = *connIt;

            if (event.events & EPOLLERR)
            {
                listener_->onError(conn);
            }
            if (event.events & EPOLLIN)
            {
                try
                {
                    if (connIt->readToBuf())
                        listener_->onReadAvailable(conn);
                } catch (const TcpException &)
                {
                    listener_->onError(conn);
                }
            }
            if (event.events & EPOLLRDHUP)
            {
                listener_->onClose(conn);
                connections_.erase(connIt);
                continue;
            }
            if (event.events & EPOLLOUT)
            {
                try
                {
                    connIt->writeFromBuf();
                    if (conn.writeBuf().empty())
                        listener_->onWriteDone(conn);
                } catch (const TcpException &)
                {
                    listener_->onError(conn);
                }
            }
        }
    }
}

} // namespace net