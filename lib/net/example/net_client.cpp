#include "server.h"
#include "connection.h"
#include "tcp_exception.h"
#include <iostream>
#include <vector>
#include <future>

std::string sendMessage(const std::string &message)
{
    try
    {
        tcp::Connection conn("127.0.0.1", 8000);
        if (std::rand() % 2)
            conn.setNonBlocking();

        conn.write(message.data(), message.size());

        std::string answer(128, 0);
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
    constexpr size_t NUM_CLIENTS = 100;
    std::vector<std::future<std::string>> futures;

    for (int i = 0; i < NUM_CLIENTS; ++i)
    {
        futures.push_back(std::async(sendMessage, std::to_string(i) + "\r\n"));
    }

    for (int i = 0; i < NUM_CLIENTS; ++i)
    {
        std::cout << futures[i].get() << std::endl;
    }

    return 0;
}