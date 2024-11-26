#pragma once
#include "CounterFactory.h"

#include "../WinCounter/WinCounter.h"

ICounter* CounterFactory::CreateCounter()
{
#ifdef _WIN32
    return WinCounter::Create();
#else
    throw new std::exception();
#endif
}
