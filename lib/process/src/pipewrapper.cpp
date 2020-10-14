#include "pipewrapper.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <cstring>

namespace process
{

PipeWrapper::PipeWrapper() : pipeFd_{-1, -1} {}

PipeWrapper::~PipeWrapper()
{
    close();
}

void PipeWrapper::open()
{
    if (::pipe2(pipeFd_, O_CLOEXEC) < 0)
        throw std::runtime_error(strerror(errno));
}

void PipeWrapper::close()
{
    closeIn();
    closeOut();
}

void PipeWrapper::closeIn()
{
    ::close(pipeFd_[0]);
    pipeFd_[0] = -1;
}

void PipeWrapper::closeOut()
{
    ::close(pipeFd_[1]);
    pipeFd_[1] = -1;
}

int PipeWrapper::getInFd() const
{
    return pipeFd_[0];
}

int PipeWrapper::getOutFd() const
{
    return pipeFd_[1];
}

} // namespace process