#include "process.h"
#include <iostream>

int main()
{
    process::Process process("cat", {"-E"});

    const char message[] = "Hello, world!\n";
    process.write(message, sizeof(message));

    char str[sizeof(message) + 1];
    process.read(str, sizeof(message) + 1);

    std::cout << str << std::endl;

    process.close();
    try
    {
        process.write(message, sizeof(message));
    } catch (const std::runtime_error& err)
    {
        std::cout << "Error: " << err.what() << std::endl;
    }

    return 0;
}