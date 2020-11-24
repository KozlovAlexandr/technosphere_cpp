#include "http.h"
#include "epoll_wrapper.h"
#include "http_connection.h"
#include "tcp_server.h"
#include <thread>
#include <bits/socket.h>
#include <shared_mutex>
#include <functional>

namespace http
{
class HttpServer
{
public:
    [[noreturn]] void run(unsigned threadsNum);
    void work(int i);
    void open(const std::string &ipAddress, unsigned short port, int maxConnections = SOMAXCONN);
    void close();

    template<typename Callback>
    void setCallback(Callback onRequest)
    {
        onRequest_ = onRequest;
    }

private:
    std::unordered_map<int, HttpConnection> connections_;

    std::shared_mutex mutex;
    tcp::Server server_;
    net::EpollDescriptor serverEpoll_;
    net::EpollDescriptor workersEpoll_;
    std::vector<std::thread> threads_;

    std::function<void(HttpRequest& request, HttpConnection &conn)> onRequest_;
    void removeConnection(int fd);
};
}