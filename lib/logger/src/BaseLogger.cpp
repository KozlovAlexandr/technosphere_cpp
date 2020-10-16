#include "BaseLogger.h"

namespace log
{

void BaseLogger::debug(const std::string &message)
{
    log(message, Level::DEBUG);
}

void BaseLogger::info(const std::string &message)
{
    log(message, Level::INFO);
}

void BaseLogger::warn(const std::string &message)
{
    log(message, Level::WARN);
}

void BaseLogger::error(const std::string &message)
{
    log(message, Level::ERROR);
}

void BaseLogger::setLevel(const Level level)
{
    level_ = level;
}

Level BaseLogger::level() const
{
    return level_;
}

BaseLogger::BaseLogger(Level level) : level_(level) {}

} // namespace log