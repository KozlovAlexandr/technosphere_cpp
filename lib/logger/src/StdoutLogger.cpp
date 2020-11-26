#include "StdoutLogger.h"
#include <iostream>

namespace log
{

StdoutLogger::StdoutLogger(Level level) : BaseLogger(std::cout, level) {}

StdoutLogger::~StdoutLogger()
{
    flush();
}

} // namespace log