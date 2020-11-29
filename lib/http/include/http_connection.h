#pragma once
#include "buffered_connection.h"
#include "http.h"
#include "Logger.h"
#include <string>

namespace http
{

class HttpConnection : public net::BufferedConnection
{
public:
    using net::BufferedConnection::BufferedConnection;

    bool doKeepAlive() const;

    bool readRequest();   // return true, if the request was read successfully
    bool writeResponse(); // return true, if the whole response was sent

    const HttpRequest& getRequest() const;
    void setResponse(const HttpResponse& response);

private:
    HttpRequest request_;
};

} // namespace http