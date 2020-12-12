#include "http.h"
#include <sstream>

namespace http
{

std::string HttpMessage::getHeaderValue(const std::string &key) const
{
    if (headers_.find(key) == headers_.end())
        return "";

    return headers_.at(key);
}

const std::string& HttpMessage::getBody() const
{
    return body_;
}

const std::string& HttpMessage::getVersion() const
{
    return version_;
}

void HttpMessage::readHeaders(std::istringstream &sstream)
{
    std::string line;

    while (std::getline(sstream, line) && line != "\r")
    {
        if (line.empty() || line.back() != '\r')
            throw HttpException("invalid http request");
        line.pop_back();

        size_t sepPos = line.find(':');
        if (sepPos == std::string::npos)
            throw HttpException("bad header");

        try {
            auto headerValuePos = line.find_first_not_of(' ', sepPos + 1);
            headers_[line.substr(0, sepPos)] = line.substr(headerValuePos);
        } catch (const std::out_of_range&) {
            throw HttpException("bad header");
        }
    }

    if (sstream.eof())
    {
        throw HttpException("invalid http request");
    }
}

void HttpMessage::readBody(std::istringstream &sstream)
{
    if (headers_.find("Content-Length") == headers_.end())
        return;

    try
    {
        int len = std::stoi(headers_["Content-Length"]);
        body_ = sstream.str().substr(sstream.tellg(), len);
    } catch (...)
    {
        throw HttpException("bad Content-Length");
    }
}

void HttpMessage::readVersion(std::istringstream &sstream)
{
    std::string versionString;
    sstream >> versionString;
    if (versionString.find("HTTP/") != 0)
        throw HttpException("bad version string");
    version_ = versionString.substr(sizeof("HTTP/") - 1);
}

void HttpRequest::readRequestLine(std::istringstream &lineStream)
{
    lineStream >> method_;

    if (method_ != "GET" && method_ != "POST")
    {
        throw HttpException("this method is not supported");
    }

    lineStream >> uri_;
    if (uri_.empty())
    {
        throw HttpException("no uri");
    }

    HttpMessage::readVersion(lineStream);
}

void HttpResponse::readStatusLine(std::istringstream &lineStream)
{
    HttpMessage::readVersion(lineStream);

    lineStream >> statusCode_;

    if (lineStream.fail())
        throw HttpException("bad status code");

    reasonPhrase_ = lineStream.str().substr(lineStream.tellg());
    reasonPhrase_ = reasonPhrase_.substr(reasonPhrase_.find_first_not_of(' '));
}

std::string HttpMessage::headersAndBodyToString() const
{
    std::string result;
    for (auto const& [header, value] : headers_)
    {
        result += header;
        result += ": ";
        result += value;
        result += "\r\n";
    }

    result += "\r\n";
    result += body_;

    return result;
}

void HttpMessage::setBody(const std::string &body)
{
    body_ = body;
}

void HttpMessage::setVersion(const std::string &version)
{
    version_ = version;
}

void HttpMessage::addHeader(const std::string &key, const std::string &value)
{
    headers_[key] = value;
}

void HttpMessage::clear()
{
    headers_.clear();
    version_.clear();
    body_.clear();
}

void HttpRequest::fromString(const std::string &request)
{
    clear();

    std::istringstream sstream(request);
    std::string line;
    std::getline(sstream, line);

    if (line.empty() || line.back() != '\r')
        throw HttpException("invalid http request");

    std::istringstream lineStream(line);

    readRequestLine(lineStream);
    HttpMessage::readHeaders(sstream);

    HttpMessage::readBody(sstream);
}

std::string HttpRequest::toString() const
{
    std::string firstLine = method_ + ' ' + uri_ + ' ' + "HTTP/" + version_ + "\r\n";

    return firstLine + HttpMessage::headersAndBodyToString();
}

HttpRequest::HttpRequest(const std::string &requestString)
{
    fromString(requestString);
}

const std::string &HttpRequest::getMethod() const
{
    return method_;
}

const std::string &HttpRequest::getUri() const
{
    return uri_;
}

void HttpRequest::setMethod(const std::string &method)
{
    method_ = method;
}

void HttpRequest::setUri(const std::string &uri)
{
    uri_ = uri;
}

void HttpRequest::clear()
{
    HttpMessage::clear();
    method_.clear();
    uri_.clear();
}

void HttpResponse::fromString(const std::string &response)
{
    clear();

    std::istringstream sstream(response);
    std::string line;
    std::getline(sstream, line);
    if (line.back() != '\r')
        throw HttpException("No \\r at the end of line");
    line.pop_back();

    std::istringstream lineStream(line);

    readStatusLine(lineStream);
    HttpMessage::readHeaders(sstream);
    HttpMessage::readBody(sstream);
}

std::string HttpResponse::toString() const
{
    std::string statusLine = "HTTP/" + version_ + ' ' + std::to_string(statusCode_) + ' ' + reasonPhrase_ + "\r\n";
    return statusLine + HttpMessage::headersAndBodyToString();
}

HttpResponse::HttpResponse(const std::string &responseString)
{
    fromString(responseString);
}

int HttpResponse::getStatusCode() const
{
    return statusCode_;
}

const std::string &HttpResponse::getReasonPhrase() const
{
    return reasonPhrase_;
}

void HttpResponse::setStatusCode(int statusCode)
{
    statusCode_ = statusCode;
}

void HttpResponse::setReasonPhrase(const std::string &reasonPhrase)
{
    reasonPhrase_ = reasonPhrase;
}

void HttpResponse::clear()
{
    HttpMessage::clear();
    reasonPhrase_.clear();
    statusCode_ = 0;
}

} // namespace http