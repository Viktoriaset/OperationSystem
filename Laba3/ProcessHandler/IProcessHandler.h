#pragma once

#include <string>

#include "../Ibase.h"

class IProcessHandler: public IBase
{
    virtual void StartLogging () = 0;
    virtual void StartCounterUpscale() = 0;
protected:
    ~IProcessHandler() = default;
public:
    virtual void CreateCrossPlatformProcess(const std::string& executable, const std::string& arguments = "") = 0;
    virtual void SetCount(int value) = 0;
};
