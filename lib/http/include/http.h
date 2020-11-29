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

class HttpMessage
{
public:
    std::string getHeaderValue(const std::string& key) const;
    const std::string& getBody() const;
    const std::string& getVersion() const;

    void setBody(const std::string &body);
    void setVersion(const std::string &version);
    void addHeader(const std::string& key, const std::string &value);

    std::string headersAndBodyToString() const;
    void clear();

protected:
    void readHeaders(std::istringstream &sstream);
    void readBody(std::istringstream &sstream);
    void readVersion(std::istringstream &sstream);

    std::unordered_map<std::string, std::string> headers_;
    std::string body_;
    std::string version_;
};

class HttpRequest : public HttpMessage
{
public:
    HttpRequest() = default;
    explicit HttpRequest(const std::string &requestString);
    void fromString(const std::string &requestString);
    std::string toString() const;

    const std::string& getMethod() const;
    const std::string& getUri() const;

    void setMethod(const std::string &method);
    void setUri(const std::string &uri);

    void clear();

private:
    void readRequestLine(std::istringstream &lineStream);

    std::string method_;
    std::string uri_;
};

class HttpResponse : public HttpMessage
{
public:
    HttpResponse() = default;
    explicit HttpResponse(const std::string &responseString);
    void fromString(const std::string &requestString);
    std::string toString() const;

    int getStatusCode() const;
    const std::string& getReasonPhrase() const;

    void setStatusCode(int statusCode);
    void setReasonPhrase(const std::string &reasonPhrase);

    void clear();

private:
    void readStatusLine(std::istringstream &sstream);

    int statusCode_{};
    std::string reasonPhrase_;
};

} // namespace http