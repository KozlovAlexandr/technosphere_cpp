#include "StdoutLogger.h"
#include <iostream>

namespace log
{

StdoutLogger::~StdoutLogger()
{
    StdoutLogger::flush();
}

void StdoutLogger::flush()
{
    std::cout.flush();
}

void StdoutLogger::log(const std::string &message, const log::Level level)
{
    if (level >= this->level())
    {
        std::cout << message << "\n";
        if (std::cout.fail())
            throw LoggerException("cannot write to stdout");
    }
}

}