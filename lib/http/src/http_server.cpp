#include "http_server.h"
#include "Logger.h"
#include <sstream>
#include <iostream>

namespace http
{
    void HttpServer::work(int i)
    {
        while (true)
        {
            std::vector<epoll_event> epollQueue = workersEpoll_.wait();

            log::debug(std::to_string(i) + " thread woke up");

            for (const epoll_event &event : epollQueue)
            {
                std::shared_lock<std::shared_mutex> sharedLock{mutex};

                if (connections_.find(event.data.fd) == connections_.end())
                    continue;

                log::info("Thread " + std::to_string(i) + " on descriptor " + std::to_string(event.data.fd) + " with events "
                    + std::to_string(event.events));

                HttpConnection &conn = connections_.at(event.data.fd);

                if (event.events & EPOLLIN)
                {
                    try {
                        conn.readToBuf();
                        HttpRequest request(conn.readBuf());
                        conn.readBuf().clear();
                        log::debug(request.toString());
                        log::debug("request is ready on descriptor " + std::to_string(conn.getFd()));
                        onRequest_(request, conn);
                        conn.unsubscribeRead();
                    } catch (const HttpException &) {
                        log::debug("request is not ready");
                        conn.subscribeRead();
                    } catch (const TcpException &) {
                        log::debug("error happened on descriptor" + std::to_string(conn.getFd()));
                    }
                } else if (event.events & EPOLLOUT)
                {
                    try {
                        conn.writeFromBuf();
                        log::debug("request was sent to descriptor " + std::to_string(conn.getFd()));
                        if (conn.writeBuf().empty())
                            log::debug("entire request was successfully sent");
                        else
                        {
                            log::info("subscibe  write on descriptor " + std::to_string(conn.getFd()));
                            conn.subscribeWrite();
                            continue;
                        }
                    } catch (const TcpException &) {
                        log::debug("Error happened on descriptor" + std::to_string(conn.getFd()));
                        continue;
                    }

                    if (!conn.keepAlive)
                    {
                        conn.close();

                        sharedLock.unlock();

                        // remove conn from map
                        std::unique_lock<std::shared_mutex> lock{mutex};
                        log::debug("Client on descriptor " + std::to_string(event.data.fd) + " disconnected");
                        connections_.erase(event.data.fd);
                    } else
                    {
                        conn.unsubscribeWrite();
                        conn.subscribeRead();
                    }
                }
            }
        }
    }

    [[noreturn]] void HttpServer::run(unsigned threadsNum)
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
                    HttpConnection newConn = HttpConnection(server_.accept(), workersEpoll_, EPOLLONESHOT | EPOLLET);
                    newConn.setNonBlocking();
                    newConn.setTimeout(5000);
                    int connFd = newConn.getFd();
                    std::unique_lock<std::shared_mutex> lock(mutex);
                    connections_.emplace(connFd, std::move(newConn));

                    log::debug("New connection on descriptor " + std::to_string(connFd));

                    serverEpoll_.add(connFd, EPOLLRDHUP);
                    connections_.at(connFd).subscribeRead();
                }
                if (event.events & EPOLLRDHUP)
                {
                    // remove conn from map
                    std::unique_lock<std::shared_mutex> lock(mutex);
                    log::info("Client on descriptor " + std::to_string(event.data.fd) + " disconnected");
                    connections_.erase(event.data.fd);
                }
            }
        }
    }

    void HttpServer::open(const std::string &ipAddress, unsigned short port, int maxConnections)
    {
        log::initWithStdoutLogger(log::Level::INFO);
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

        connections_.clear();
    }
}