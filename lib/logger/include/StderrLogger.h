#ifndef LOGGER_STDERRLOGGER_H
#define LOGGER_STDERRLOGGER_H

#include "BaseLogger.h"

namespace log
{

class StderrLogger : public BaseLogger
{
public:
    explicit StderrLogger(Level level = Level::INFO);
};

} // namespace log

#endif //LOGGER_STDERRLOGGER_H
