#ifndef PROCESS_LOGGER_H
#define PROCESS_LOGGER_H

#include "BaseLogger.h"
#include "StdoutLogger.h"
#include "StderrLogger.h"
#include "FileLogger.h"
#include <memory>

namespace log
{

class Logger
{
public:
    Logger(const Logger &logger) = delete;
    Logger &operator=(const Logger &logger) = delete;
    Logger(Logger &&logger) = delete;
    Logger &operator=(Logger &&logger) = delete;

    static Logger& getInstance();

    void setGlobalLogger(std::unique_ptr<BaseLogger> logger);
    BaseLogger & getGlobalLogger();

private:
    Logger() = default;
    std::unique_ptr<BaseLogger> globalLogger_;
};

void initWithFileLogger(const std::string &filename, Level level = Level::WARN);
void initWithStderrLogger(Level level = Level::WARN);
void initWithStdoutLogger(Level level = Level::WARN);

void debug(const std::string &message);
void info(const std::string &message);
void warn(const std::string &message);
void error(const std::string &message);

} // namespace log

#endif //PROCESS_LOGGER_H
