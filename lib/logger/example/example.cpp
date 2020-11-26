#include <StderrLogger.h>
#include "FileLogger.h"
#include "StdoutLogger.h"
#include "Logger.h"

int main()
{
    log::initWithStdoutLogger();

    log::debug("DEBUG");
    log::info("INFO");
    log::warn("WARN");
    log::error("ERROR");

    log::initWithFileLogger("logs.txt", log::Level::INFO);

    log::debug("DEBUG");
    log::info("INFO");
    log::warn("WARN");
    log::error("ERROR");

    log::initWithStderrLogger(log::Level::ERROR);

    log::debug("DEBUG");
    log::info("INFO");
    log::warn("WARN");
    log::error("ERROR");

    return 0;
}