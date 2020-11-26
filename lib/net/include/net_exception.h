#pragma once

#include <stdexcept>
#include "tcp_exception.h"

class NetException : public TcpException
{
public:
    using TcpException::TcpException;
};

class TimeoutNetException : public NetException
{
public:
    using NetException::NetException;
};