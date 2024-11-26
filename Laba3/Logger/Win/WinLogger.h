#pragma once
#include "../Ilogger.h"
#include <string>
#include <Windows.h>

class WinLogger : public ILogger
{
    WinLogger();
    std::wstring GetLogFileName(std::string fileName);
    HANDLE File;

protected:
    ~WinLogger() override;
    
public:
    void Delete() override;
    void Log(std::string info) override;

    static ILogger* Create();
};
