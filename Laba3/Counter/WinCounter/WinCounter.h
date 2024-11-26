#pragma once
#include "../Counter.h"
#include <Windows.h>


class WinCounter : public ICounter
{
    const char* MUTEX_NAME = "CounterMutex";
    HANDLE hMutex;
    WinCounter();

protected:
    ~WinCounter();
    
public:
    void Delete() override;
    int GetCount() override;
    void Increment() override;
    void SetCount(int value) override;

    static ICounter* Create();
};
