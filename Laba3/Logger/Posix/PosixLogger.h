#pragma once
#include "../Ilogger.h"

class PosixLogger : public ILogger
{
    PosixLogger();
    std::wstring GetLogFileName(std::string fileName);  

protected:
    ~PosixLogger();
    
public:
    void Delete() override;
    void Log(std::string info) override;

    static ILogger* Create();
};
