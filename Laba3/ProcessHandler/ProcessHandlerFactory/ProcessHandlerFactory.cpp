#include "ProcessHandlerFactory.h"
#include "../Win/WinProcessHandler.h"

IProcessHandler* ProcessHandlerFactory::Create(ILogger* logger, ICounter* counter, ITimer* timer)
{
#ifdef _WIN32
    return WinProcessHandler::Create(logger, counter, timer);
#else
    return PosixProcessHandler::Create(logger, counter, timer);// TODO
#endif
}