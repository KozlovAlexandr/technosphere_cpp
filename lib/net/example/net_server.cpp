#include <iostream>
#include <service.h>

class EchoListener : public net::IServiceListener
{
    void onNewConnection(net::BufferedConnection &conn) override
    {
        std::cout << "New client connected on descriptor " << conn.getFd() << std::endl;
        conn.subscribeRead();
    }

    void onClose(net::BufferedConnection &conn) override
    {
        std::cout << "Client disconnected on descriptor " << conn.getFd() << std::endl;
    }

    void onWriteDone(net::BufferedConnection &conn) override
    {
        std::cout << "Successful write to client on descriptor " << conn.getFd() << std::endl;
        conn.subscribeRead();
        conn.unsubscribeWrite();
    }

    void onReadAvailable(net::BufferedConnection &conn) override
    {
        std::cout << "Reading from client on descriptor " << conn.getFd() << std::endl;

        std::string &message = conn.readBuf();
        auto endIt = message.find("\r\n");
        if (endIt == std::string::npos)
            return;

        message.resize(endIt);
        std::string answer = "You sent: " + message + "\n";

        message.clear();
        conn.writeBuf().append(answer);

        conn.subscribeWrite();
        conn.unsubscribeRead();
    }

    void onError(net::BufferedConnection &conn) override
    {
        std::cerr << "Error happened on client on descriptor " << conn.getFd() << std::endl;
    }
};


int main()
{
    EchoListener listener;
    net::Service service;

    service.setListener(&listener);
    service.open("127.0.0.1", 8000);
    service.run();
    return 0;
}