#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include "shared_map.h"

using namespace shmem;

int main()
{
    size_t blocks_count = 100;
    size_t block_size = 128;

    SharedMap<int, std::string> sharedMap(block_size, blocks_count);

    if (!fork())
    {
        sharedMap.insert(3, "This is a string long enough not to use the small string optimization");
        return 0;
    }

    wait(nullptr);
    std::cout << sharedMap.get(3) << std::endl;
    sharedMap.deleteMap();

    return 0;
}