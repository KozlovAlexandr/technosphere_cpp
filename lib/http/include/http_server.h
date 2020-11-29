#include "http_connection.h"
#include "tcp_server.h"
#include <thread>
#include <shared_mutex>
#include <functional>

namespace http
{

class HttpServer
{
public:
    void run(unsigned threadsNum);
    void open(const std::string &ipAddress, unsigned short port, int maxConnections = SOMAXCONN);
    void close();

    template<typename Callback>
    void setCallback(Callback onRequest)
    {
        onRequest_ = onRequest;
    }

private:
    void work(int i);
    void removeConnection(int fd);

    std::unordered_map<int, HttpConnection> connections_;
    std::vector<std::thread> threads_;

    std::shared_mutex mutex_;
    tcp::Server server_;
    net::EpollDescriptor serverEpoll_;
    net::EpollDescriptor workersEpoll_;

    std::function<void(HttpServer& server, HttpConnection &conn)> onRequest_;
};

}  // namespace http