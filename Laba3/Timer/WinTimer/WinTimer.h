#pragma once
#include "../ITimer.h"

class WinTimer : public ITimer
{
    WinTimer();

protected:
    ~WinTimer() override;
    
public:
    void Delete() override;
    time_t Time() override;
    void Sleep(int seconds, int milliseconds = 0) override;
    std::string GetDateTime() override;

    static ITimer* Create();
};
