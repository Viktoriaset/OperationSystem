#pragma once
#include <string>
#include <ctime>

#include "../Ibase.h"

class ITimer : public IBase
{
protected:
    ~ITimer() = default;
public:
    virtual time_t Time() = 0;
    virtual void Sleep(int seconds, int milleseconds = 0) = 0;
    virtual std::string GetDateTime() = 0;
};
