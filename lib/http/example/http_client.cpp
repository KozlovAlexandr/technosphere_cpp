#include "tcp_server.h"
#include "http.h"
#include <iostream>
#include <vector>
#include <future>

std::string sendMessage(int i)
{
    try
    {
        tcp::Connection conn("127.0.0.1", 8000);
        if (std::rand() % 2)
            conn.setNonBlocking();


        http::HttpRequest request;
        request.setMethod("GET");
        request.setVersion("1.1");
        request.setUri("/");
        request.addHeader("User-Agent", std::to_string(i));

        std::string message = request.toString();

        conn.write(message.data(), message.size());

        std::string answer(8192, 0);
        int bytesRead = conn.read(answer.data(), answer.size());
        answer.resize(bytesRead);

        return answer;
    }
    catch (const TcpException &)
    {
        return "Oops, something bad happened";
    }
}

int main()
{
    std::srand(time(nullptr));
    constexpr size_t NUM_CLIENTS = 10000;
    std::vector<std::future<std::string>> futures;

    for (int i = 0; i < NUM_CLIENTS; ++i)
    {
        futures.push_back(std::async(sendMessage, i));
    }

    for (int i = 0; i < NUM_CLIENTS; ++i)
    {
        std::cout << futures[i].get() << std::endl;
    }

    return 0;
}
