#pragma once
#include "../Counter.h"

class CounterFactory
{
public:
    static ICounter* CreateCounter();
};
