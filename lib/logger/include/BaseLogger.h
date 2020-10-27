#ifndef LOGGER_BASELOGGER_H
#define LOGGER_BASELOGGER_H

#include <string>
#include <stdexcept>

namespace log
{

enum class Level
{
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class BaseLogger
{
public:
    explicit BaseLogger(std::ostream &outStream, Level level = Level::WARN);
    virtual ~BaseLogger() = default;

    void debug(const std::string &message);
    void info(const std::string &message);
    void warn(const std::string &message);
    void error(const std::string &message);

    void setLevel(Level level);
    [[nodiscard]] Level level() const;

    void flush();

protected:
    virtual void log(const std::string &message, Level level);

private:
    std::ostream &outStream_;
    Level level_;
};

class LoggerException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

} // namespace log

#endif //LOGGER_BASELOGGER_H
