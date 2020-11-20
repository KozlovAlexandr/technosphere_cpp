#pragma once
#include "buffered_connection.h"

namespace http
{

class HttpConnection : public net::BufferedConnection
{
    using net::BufferedConnection::BufferedConnection;

public:
    bool keepAlive = false;
};

}