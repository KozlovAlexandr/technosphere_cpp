#include "Logger.h"

namespace log
{

    Logger& Logger::getInstance()
    {
        static Logger globalLogger;
        return globalLogger;
    }

    void Logger::setGlobalLogger(std::unique_ptr<BaseLogger> newLogger)
    {
        if (!newLogger)
            throw LoggerException("bad logger pointer");

        globalLogger_ = std::move(newLogger);
    }

    BaseLogger& Logger::getGlobalLogger()
    {
        if (!globalLogger_)
            throw LoggerException("global logger has not been set yet");

        return  *globalLogger_;
    }

    void initWithFileLogger(const std::string &filename, Level level)
    {
        Logger::getInstance().setGlobalLogger(std::make_unique<FileLogger>(filename, level));
    }

    void initWithStdoutLogger(Level level)
    {
        Logger::getInstance().setGlobalLogger(std::make_unique<StdoutLogger>(level));
    }

    void initWithStderrLogger(Level level)
    {
        Logger::getInstance().setGlobalLogger(std::make_unique<StderrLogger>(level));
    }

    void debug(const std::string &message)
    {
        Logger::getInstance().getGlobalLogger().debug(message);
    }

    void info(const std::string &message)
    {
        Logger::getInstance().getGlobalLogger().info(message);
    }

    void warn(const std::string &message)
    {
        Logger::getInstance().getGlobalLogger().warn(message);
    }

    void error(const std::string &message)
    {
        Logger::getInstance().getGlobalLogger().error(message);
    }

} // namespace log