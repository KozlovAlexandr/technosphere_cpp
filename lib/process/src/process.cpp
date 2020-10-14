#include "process.h"
#include <unistd.h>
#include <stdexcept>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <algorithm>

namespace
{
    std::vector<char*> makeArgsToPass(std::string &path, std::vector<std::string> &args)
    {
        std::vector<char*> res;

        res.push_back(path.data());
        std::transform(args.begin(), args.end(), std::back_inserter(res),
                       [](std::string &s) { return s.data(); });
        res.push_back(nullptr);

        return res;
    }
}

namespace process
{

Process::Process(const std::string &path, const std::vector<std::string> &args)
{
    readPipe.open();
    writePipe.open();

    pid_t pid = ::fork();
    if (pid < 0)
    {
        throw std::runtime_error(::strerror(errno));
    }
    if (pid == 0)
    {
        std::string pathCopy = path;
        std::vector<std::string> argsCopy = args;
        std::vector<char*> argsToPass = makeArgsToPass(pathCopy, argsCopy);

        if (dup2(readPipe.getOutFd(), STDOUT_FILENO) < 0 ||  dup2(writePipe.getInFd(), STDIN_FILENO) < 0)
            throw std::runtime_error(strerror(errno));

        execvp(path.data(), argsToPass.data()); // after this call pipe's descriptors will be closed
                                                // automatically as created with O_CLOEXEC flag

        exit(EXIT_FAILURE);
    }

    readPipe.closeOut();
    writePipe.closeIn();

    pid_ = pid;
}

Process::~Process()
{
    close();
}

size_t Process::write(const void *data, size_t len)
{
    ssize_t bytesWritten = ::write(writePipe.getOutFd(), data, len);
    if (bytesWritten < 0)
        throw std::runtime_error(strerror(errno));

    return bytesWritten;
}

size_t Process::read(void *data, size_t len)
{
    ssize_t bytesRead = ::read(readPipe.getInFd(), data, len);
    if (bytesRead < 0)
        throw std::runtime_error(strerror(errno));

    return bytesRead;
}

void Process::readExact(void *data, size_t len)
{
    size_t bytesTotalRead = 0;

    while (bytesTotalRead != len)
    {
        size_t bytesRead = read(static_cast<char*>(data) + bytesTotalRead, len - bytesTotalRead);
        if (!bytesRead)
            throw std::runtime_error("Pipe for reading was closed");

        bytesTotalRead += bytesRead;
    }
}

void Process::writeExact(const void *data, size_t len)
{
    size_t bytesWritten = 0;

    while (bytesWritten != len)
    {
        bytesWritten += write(static_cast<const char*>(data) + bytesWritten, len - bytesWritten);
    }
}

void Process::closeStdin()
{
    writePipe.closeOut();
}

void Process::close()
{
    readPipe.closeIn();
    writePipe.closeOut();

    kill(pid_, SIGINT);
    waitpid(pid_, nullptr, 0);
}

} // namespace process
