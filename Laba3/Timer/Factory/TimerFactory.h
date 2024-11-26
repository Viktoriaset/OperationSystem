#pragma once
#include "../ITimer.h"

class TimerFactory
{
public:
    static ITimer* CreateTimer();   
};
