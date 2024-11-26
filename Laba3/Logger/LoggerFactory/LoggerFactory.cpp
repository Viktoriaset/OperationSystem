#include "LoggerFactory.h"
#include "../Win/WinLogger.h"
#include "../Posix/PosixLogger.h"

ILogger* LoggerFactory::CreateLogger()
{
#ifdef _WIN32
    return WinLogger::Create();
#else
    return PosixLogger::Create();
#endif
}