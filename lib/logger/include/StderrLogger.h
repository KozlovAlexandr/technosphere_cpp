#ifndef LOGGER_STDERRLOGGER_H
#define LOGGER_STDERRLOGGER_H

#include "BaseLogger.h"

namespace log
{

class StderrLogger : public BaseLogger
{
public:
    using BaseLogger::BaseLogger;
    ~StderrLogger() override = default;

    void flush() override;

private:
    void log(const std::string &message, Level level) override;
};

} // namespace log

#endif //LOGGER_STDERRLOGGER_H
