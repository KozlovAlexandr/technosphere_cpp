#include "FileLogger.h"

namespace log
{

FileLogger::FileLogger(const std::string &filename, log::Level level) : BaseLogger(level)
{
    fileStream_.open(filename, std::ios_base::out);
    if (fileStream_.fail())
        throw LoggerException("cannot open file");
}

void FileLogger::flush()
{
    fileStream_.flush();
}

void FileLogger::log(const std::string &message, log::Level level)
{
    if (level >= this->level())
    {
        fileStream_ << message << "\n";
        if (fileStream_.fail())
            throw LoggerException("cannot write to file");
    }
}

}

