#pragma once
#include "../Ibase.h"

class ICounter : public IBase
{
protected:
    int count = 0;
    ~ICounter() = default;

public:
    virtual int GetCount() = 0;
    virtual void Increment() = 0;
    virtual void SetCount(int value) = 0;
};
