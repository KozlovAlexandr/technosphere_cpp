#include "http_server.h"
#include "Logger.h"
#include <sstream>
#include <iostream>

namespace
{
    constexpr size_t MAX_REQUEST_SIZE = 8 * 1024 * 1024; // 8 MB
}

namespace http
{

void HttpServer::work(int i)
{
    while (true)
    {
        std::vector<epoll_event> epollQueue = workersEpoll_.wait();

        for (const epoll_event &event : epollQueue)
        {
            log::debug("Thread " + std::to_string(i) + " on descriptor " + std::to_string(event.data.fd)
                       + " with events " + std::to_string(event.events));

            std::shared_lock<std::shared_mutex> sharedLock{mutex_};
            if (connections_.find(event.data.fd) == connections_.end())
                continue;
            HttpConnection &conn = connections_.at(event.data.fd);
            sharedLock.unlock();

            try
            {
                if (event.events & EPOLLRDHUP)
                {
                    log::info("Client on  descriptor " + std::to_string(event.data.fd) + " disconnected");
                    removeConnection(event.data.fd);
                } else if (event.events & EPOLLERR)
                {
                    log::error("Error happened on client on descriptor " + std::to_string(event.data.fd));
                } else if (event.events & EPOLLIN)
                {
                    processRequest(conn);
                } else if (event.events & EPOLLOUT)
                {
                    sendResponse(conn);
                }
            } catch (const TcpException&)
            {
                log::error("Error happened on client on descriptor " + std::to_string(event.data.fd));
            }
        }
    }
}

void HttpServer::run(unsigned threadsNum)
{
    for (int i = 0; i < std::min(std::thread::hardware_concurrency(), threadsNum); ++i)
    {
        threads_.emplace_back(&HttpServer::work, this, i);
    }

    while (true)
    {
        std::vector<epoll_event> epollQueue = serverEpoll_.wait();

        for (const epoll_event &event : epollQueue)
        {
            if (event.events & EPOLLIN)
            {
                try
                {
                    HttpConnection newConn{server_.accept(), workersEpoll_,EPOLLONESHOT | EPOLLET};
                    newConn.setNonBlocking();

                    int connFd = newConn.getFd();
                    log::info("New connection on descriptor " + std::to_string(connFd));

                    std::unique_lock<std::shared_mutex> lock{mutex_};
                    try
                    {
                        connections_.emplace(connFd, std::move(newConn));
                        connections_.at(connFd).subReadSubClose();
                    } catch (const TcpException &e)
                    {
                        log::error(std::string{"cant subscribe for new connection on descriptor "} +
                            std::to_string(connFd) + " " + e.what());
                        connections_.erase(connFd);
                    }
                } catch (const TcpException& e)
                {
                    log::error(std::string{"can't create new connection "} + e.what());
                    continue;
                }
            }
        }
    }
}

void HttpServer::open(const std::string &ipAddress, unsigned short port, int maxConnections)
{
    log::initWithStdoutLogger(log::Level::ERROR);
    tcp::Server tmpServer(ipAddress, port, maxConnections);
    tmpServer.setNonBlocking();

    net::EpollDescriptor tmpServerEpoll;
    tmpServerEpoll.open();
    tmpServerEpoll.add(tmpServer.getFd(), EPOLLIN);

    net::EpollDescriptor tmpWorkerEpoll;
    tmpWorkerEpoll.open();

    server_ = std::move(tmpServer);
    serverEpoll_ = std::move(tmpServerEpoll);
    workersEpoll_ = std::move(tmpWorkerEpoll);
}

void HttpServer::close()
{
    server_.close();
    workersEpoll_.close();
    serverEpoll_.close();

    for (std::thread &th : threads_)
        th.join();
}

void HttpServer::removeConnection(int fd)
{
    std::unique_lock<std::shared_mutex> lock{mutex_};
    connections_.erase(fd);
}

void HttpServer::sendResponse(HttpConnection &conn)
{
    if (!conn.writeResponse())
    {
        conn.reactivate();
        return;
    }

    if (!conn.doKeepAlive())
    {
        log::info("Client on  descriptor " + std::to_string(conn.getFd()) + " disconnected");
        removeConnection(conn.getFd());
    } else
    {
        conn.subReadUnsubWrite();
    }
}

void HttpServer::processRequest(HttpConnection &conn)
{
    if (conn.readRequest())
    {
        onRequest_(*this, conn);
        return;
    }

    if (conn.readBuf().size() > MAX_REQUEST_SIZE)
    {
        removeConnection(conn.getFd());
    } else
    {
        conn.reactivate();
    }
}

} // namespace http