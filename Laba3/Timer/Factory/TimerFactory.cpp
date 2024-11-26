#include "TimerFactory.h"

#include "../WinTimer/WinTimer.h"

ITimer* TimerFactory::CreateTimer()
{
#if _WIN32
    return WinTimer::Create();
#else
    throw new std::exception();
#endif
    
}
