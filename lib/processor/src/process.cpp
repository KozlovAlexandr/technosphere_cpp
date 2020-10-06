#include "process.h"
#include <unistd.h>
#include <stdexcept>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <algorithm>

namespace process
{

Process::Process(const std::string &path, const std::vector<std::string> &args)
{
    int pipes[2][2];
    if (pipe2(pipes[0], O_CLOEXEC) < 0 || pipe2(pipes[1], O_CLOEXEC) < 0)
    {
        throw std::runtime_error(strerror(errno));
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        throw std::runtime_error(strerror(errno));
    }
    if (!pid)
    {
        if (dup2(pipes[0][1], 1) < 0 ||  dup2(pipes[1][0], 0) < 0)
                throw std::runtime_error(strerror(errno));

        std::vector<const char*> argsToPass;
        argsToPass.reserve(args.size() + 2);
        argsToPass.push_back(path.data());
        std::transform(args.begin(), args.end(), argsToPass.end(),
                       [](const std::string &s) { return s.data(); });

        execvp(path.data(), const_cast<char *const *>(argsToPass.data()));

        exit(EXIT_FAILURE);
    }

    ::close(pipes[0][1]);
    ::close(pipes[1][0]);

    fdRead_ = pipes[0][0];
    fdWrite_ = pipes[1][1];
    pid_ = pid;
}

Process::~Process()
{
    close();
}

size_t Process::write(const void *data, size_t len)
{
    ssize_t bytesWritten = ::write(fdWrite_, data, len);
    if (bytesWritten < 0)
        throw std::runtime_error(strerror(errno));

    return bytesWritten;
}

size_t Process::read(void *data, size_t len)
{
    ssize_t bytesRead = ::read(fdRead_, data, len);
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
    ::close(fdWrite_);
    fdWrite_ = -1;
}

void Process::close()
{
    ::close(fdRead_);
    ::close(fdWrite_);
    fdRead_ = fdWrite_= -1;

    kill(pid_, SIGINT);
    waitpid(pid_, nullptr, 0);
}

}
