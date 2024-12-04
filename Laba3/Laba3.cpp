#include "Counter/Counter.h"
#include "Counter/Factory/CounterFactory.h"
#include "Logger/Ilogger.h"
#include "Logger/LoggerFactory/LoggerFactory.h"
#include "ProcessHandler/IProcessHandler.h"
#include "Timer/ITimer.h"
#include "Timer/Factory/TimerFactory.h"
#include "ProcessHandler/ProcessHandlerFactory/ProcessHandlerFactory.h"

int main(int argc, char* argv[])
{
    ILogger *logger = LoggerFactory::CreateLogger();
    ICounter *counter = CounterFactory::CreateCounter();
    ITimer *timer = TimerFactory::CreateTimer();
    IProcessHandler *processHandler = ProcessHandlerFactory::Create(logger, counter, timer);

    processHandler->CreateCrossPlatformProcess("notepad.exe");
    return 0;
}
