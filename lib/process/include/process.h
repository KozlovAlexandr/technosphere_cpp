#ifndef SPHERE_PROCESS_H
#define SPHERE_PROCESS_H

#include "pipewrapper.h"
#include <string>
#include <vector>

namespace process
{

class Process
{
public:
    explicit Process(const std::string& path, const std::vector<std::string>& args = {});
    ~Process();

    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);

    void closeStdin();
    void close();

private:
    PipeWrapper readPipe, writePipe;
    pid_t pid_;
};

} // namespace process

#endif //SPHERE_PROCESS_H
