#include "StderrLogger.h"
#include <iostream>

namespace log
{

void StderrLogger::log(const std::string &message, const log::Level level)
{
    if (level >= this->level())
    {
        std::cerr << message << "\n";
        if (std::cerr.fail())
            throw std::runtime_error("cannot write to stderr");
    }
}

void StderrLogger::flush() {}

} // namespace log