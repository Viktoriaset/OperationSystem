#pragma once

#include "../IProcessHandler.h"
#include "../../Logger/Ilogger.h"
#include "../../Counter/Counter.h"
#include "../../Timer/ITimer.h"

class ProcessHandlerFactory
{
public:
    static IProcessHandler* Create(ILogger *logger, ICounter *counter, ITimer *timer);
};
