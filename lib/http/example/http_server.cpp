#include "http.h"
#include "http_server.h"
#include "Logger.h"
#include <iostream>

void onRequest(http::HttpServer& server, http::HttpConnection &conn)
{
    const http::HttpRequest request = conn.getRequest();
    std::string userAgent = request.getHeaderValue("User-Agent");

    http::HttpResponse response;

    response.setStatusCode(200);
    response.setVersion("1.1");
    response.setReasonPhrase("OK");

    response.setBody("<html><p> Your User-Agent: " + userAgent + "</p></html>");

    response.addHeader("Content-Length", std::to_string(response.getBody().size()));
    response.addHeader("Connection", "keep-alive");

    conn.setResponse(response);
    conn.subWriteUnsubRead();
}

int main()
{
    http::HttpServer server;
    server.setCallback(onRequest);
    server.open("127.0.0.1", 8000);
    server.run(8);

    return 0;
}