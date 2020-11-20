#pragma once

#include <unordered_map>
#include <string>
#include "net_exception.h"

class HttpException : public NetException
{
public:
    using NetException::NetException;
};


namespace http
{

struct HttpMessage
{
    std::unordered_map<std::string, std::string> headers_;
    std::string body_;
    std::string version_;

protected:
    void readHeaders(std::istringstream &sstream);
    void readBody(std::istringstream &sstream);
    void readVersion(std::istringstream &sstream);
    std::string headersAndBodyToString();
};

struct HttpRequest : HttpMessage
{
    explicit HttpRequest(const std::string &requestString);
    std::string method_;
    std::string uri_;

    void fromString(const std::string& request);
    std::string toString();
};

struct HttpResponse : HttpMessage
{
    int statusCode;
    std::string reasonPhrase_;

    void fromString(const std::string& request);
    std::string toString();
};

}