#ifndef PROCESS_FILELOGGER_H
#define PROCESS_FILELOGGER_H

#include "BaseLogger.h"
#include <fstream>

namespace log
{

class FileLogger : public BaseLogger
{
public:
    explicit FileLogger(const std::string &filename, Level level = Level::WARN);
    ~FileLogger() override = default;

    void flush() override;

private:
    void log(const std::string &message, Level level) override;
    std::ofstream fileStream_;
};

} // namespace log

#endif //PROCESS_FILELOGGER_H
