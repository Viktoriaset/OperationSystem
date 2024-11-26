#pragma once
#include "../IProcessHandler.h"
#include "../../Logger/Ilogger.h"
#include "../../Counter/Counter.h"
#include "../../Timer/ITimer.h"

class WinProcessHandler : public IProcessHandler
{
    ILogger *logger;
    ICounter *counter;
    ITimer *timer;
    WinProcessHandler(ILogger *logger, ICounter *counter, ITimer *timer);
    void StartLogging() override;
    void StartCounterUpscale() override;

protected:
    ~WinProcessHandler() override;
public:
    void Delete() override;
    void CreateCrossPlatformProcess(const std::string& executable, const std::string& arguments = "") override;
    void SetCount(int value) override;
    static IProcessHandler* Create(ILogger *logger, ICounter *counter, ITimer *timer);
};
