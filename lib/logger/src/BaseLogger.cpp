#include "BaseLogger.h"
#include <ostream>

namespace log
{

BaseLogger::BaseLogger(std::ostream &outStream, Level level) : outStream_(outStream), level_(level) {}

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

void BaseLogger::log(const std::string &message, Level level)
{
    if (level >= this->level())
    {
        outStream_ << message << "\n";
        if (outStream_.fail())
            throw LoggerException("cannot write to file");
    }
}

void BaseLogger::flush()
{
    outStream_.flush();
}

} // namespace log