#include "http.h"
#include "http_server.h"
#include "Logger.h"
#include <iostream>

void onRequest(http::HttpRequest& request, http::HttpConnection &conn)
{
    http::HttpResponse response;
    response.statusCode = 200;
    response.version_ = "1.1";
    response.reasonPhrase_ = "OK";

    response.body_ = "<html><p>Hello, world</p></html>";
    response.headers_["Content-Length"] = std::to_string(response.body_.size());

    conn.keepAlive = request.headers_["Connection"] == "keep-alive";

    conn.writeBuf().append(response.toString());

    conn.subscribeWrite();
    log::info("subscibe  write on descriptor " + std::to_string(conn.getFd()));
}

int main()
{
    http::HttpServer server;
    server.setCallback(onRequest);
    server.open("127.0.0.1", 8000);
    server.run(8);

    return 0;
}