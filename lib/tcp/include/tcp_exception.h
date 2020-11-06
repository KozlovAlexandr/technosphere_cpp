#pragma once

#include <stdexcept>

class TcpException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class TimeoutException : public TcpException
{
public:
    using TcpException::TcpException;
};
