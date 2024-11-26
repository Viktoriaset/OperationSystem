#pragma once
#include <string>
#include "../Ibase.h"

#ifndef  ILOGGER_H
#define ILOGGER_H

class ILogger : public IBase
{
protected:
    ~ILogger() = default;

public:
    virtual void Log(std::string info) = 0;
    
    const std::string FileName = "log.txt";
};

#endif
