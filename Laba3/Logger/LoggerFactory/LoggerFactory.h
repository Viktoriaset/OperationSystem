#pragma once
#include "../Ilogger.h"

class LoggerFactory
{
public:
    static ILogger* CreateLogger();
};
