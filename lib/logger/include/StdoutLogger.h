#ifndef LOGGER_STDOUTLOGGER_H
#define LOGGER_STDOUTLOGGER_H

#include "BaseLogger.h"

namespace log
{

class StdoutLogger : public BaseLogger
{
public:
    using BaseLogger::BaseLogger;
    ~StdoutLogger() override;

    void flush() override;

private:
    void log(const std::string &message, Level level) override;
};

} // namespace log

#endif //LOGGER_STDOUTLOGGER_H
