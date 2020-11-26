#include "FileLogger.h"

namespace log
{

FileLogger::FileLogger(const std::string &filename, log::Level level) : BaseLogger(fileStream_, level)
{
    fileStream_.open(filename, std::ios_base::out);
    if (fileStream_.fail())
        throw LoggerException("cannot open file");
}

} // namespace log

