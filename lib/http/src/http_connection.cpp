#include "http_connection.h"
#include "Logger.h"

namespace http
{

bool HttpConnection::readRequest()
{
    try
    {
        if (!readToBuf())
            return false;

        request_.fromString(readBuf());
        readBuf().clear();

        return true;
    } catch (const HttpException &)
    {
        reactivate();
        return false;
    }
}

const http::HttpRequest &HttpConnection::getRequest() const
{
    return request_;
}

void HttpConnection::setResponse(const HttpResponse& response)
{
    writeBuf() = response.toString();
}

bool HttpConnection::doKeepAlive() const
{
    return request_.getHeaderValue("Connection") == "keep-alive";
}

bool HttpConnection::writeResponse()
{
    writeFromBuf();
    if (!writeBuf().empty())
    {
        reactivate();
        return false;
    }

    return true;
}

} // namespace http