#ifndef LOGGER_STDOUTLOGGER_H
#define LOGGER_STDOUTLOGGER_H

#include "BaseLogger.h"

namespace log
{

class StdoutLogger : public BaseLogger
{
public:
    explicit StdoutLogger(Level level = Level::INFO);
    ~StdoutLogger() override;

    void flush() override;
};

} // namespace log

#endif //LOGGER_STDOUTLOGGER_H
