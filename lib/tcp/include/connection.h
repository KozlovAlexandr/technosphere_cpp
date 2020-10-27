#pragma once

#include <string>
#include "descriptor.h"

namespace tcp
{

class Connection
{
public:
    Connection(const std::string& ipAddress, unsigned short port);
    Connection(Connection &&connection) = default;
    Connection &operator=(Connection&& connection) = default;

    ~Connection() = default;

    void connect(const std::string& ipAddress, unsigned short port);

    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);

    void close();

    void setTimeout(unsigned msecs);

private:
    explicit Connection(int fd);

    SocketDescriptor socketDescriptor_;
    friend class Server;
};

} // namespace tcp
