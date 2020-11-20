#include "http.h"
#include <sstream>

namespace http
{
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

        try {
            int len = std::stoi(headers_["Content-Length"]);
            body_ = sstream.str().substr(sstream.tellg(), len);
        } catch (...) {
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

    std::string HttpMessage::headersAndBodyToString()
    {
        std::string result;
        for (auto const& [header, value] : headers_)
        {
            result.append(header)
                    .append(": ")
                    .append(value)
                    .append("\r\n");
        }
        result += "\r\n";
        result += body_;

        return result;
    }

    void HttpRequest::fromString(const std::string &request)
    {
        std::istringstream sstream(request);
        std::string line;
        std::getline(sstream, line);

        if (line.empty() || line.back() != '\r')
            throw HttpException("invalid http request");

        std::istringstream lineStream(line);
        lineStream >> method_;

        if (method_ != "GET" && method_ != "POST")
        {
            throw HttpException("this method is not supported");
        }

        lineStream >> uri_;

        HttpMessage::readVersion(lineStream);
        HttpMessage::readHeaders(sstream);

        HttpMessage::readBody(sstream);
    }

    std::string HttpRequest::toString()
    {
        std::string firstLine = method_ + ' ' + uri_ + ' ' + "HTTP/" + version_ + "\r\n";

        return firstLine + HttpMessage::headersAndBodyToString();
    }

    HttpRequest::HttpRequest(const std::string &requestString)
    {
        fromString(requestString);
    }

    void HttpResponse::fromString(const std::string &response)
    {
        std::istringstream sstream(response);
        std::string line;
        std::getline(sstream, line);
        if (line.back() != '\r')
            throw HttpException("No \\r at the end of line");
        line.pop_back();

        std::istringstream lineStream(line);
        HttpMessage::readVersion(lineStream);
        lineStream >> statusCode;

        reasonPhrase_ = line.substr(lineStream.tellg());
        reasonPhrase_ = reasonPhrase_.substr(reasonPhrase_.find_first_not_of(' '));

        HttpMessage::readHeaders(sstream);
        HttpMessage::readBody(sstream);
    }

    std::string HttpResponse::toString()
    {
        std::string firstLine = "HTTP/" + version_ + ' ' + std::to_string(statusCode) + ' ' + reasonPhrase_ + "\r\n";
        return firstLine + HttpMessage::headersAndBodyToString();
    }
}