#include "StderrLogger.h"
#include <iostream>

namespace log
{

StderrLogger::StderrLogger(Level level) : BaseLogger(std::cerr, level) {}

} // namespace log