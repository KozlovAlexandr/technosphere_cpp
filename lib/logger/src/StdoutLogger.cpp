#include "StdoutLogger.h"
#include <iostream>

namespace log
{

StdoutLogger::StdoutLogger(Level level) : BaseLogger(std::cout, level) {}

StdoutLogger::~StdoutLogger()
{
    StdoutLogger::flush();
}

void StdoutLogger::flush()
{
    std::cout.flush();
}

} // namespace log