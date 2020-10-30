#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include "shared_map.h"

using namespace shmem;

int main()
{
    size_t blocks_count = 100;
    size_t block_size = 128;

    SharedMap<int, std::string> s(block_size, blocks_count);

    if (!fork())
    {
        s.insert(3, "hello world fdsfdsfsdfsfsfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdf");
        return 0;
    }

    wait(nullptr);
    std::cout << s.get(3) << std::endl;

    return 0;
}