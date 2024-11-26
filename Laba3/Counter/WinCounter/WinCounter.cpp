#include "WinCounter.h"

ICounter* WinCounter::Create()
{
#ifdef _WIN32
    return new WinCounter();
#else
    throw std::exception("WinCounter::Create");
#endif
}

WinCounter::WinCounter()
{
    hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, LPWSTR(MUTEX_NAME));

    if (hMutex == NULL)
    {
        hMutex = CreateMutex(NULL, FALSE, LPWSTR(MUTEX_NAME));
    }
}

WinCounter::~WinCounter()
{
    CloseHandle(hMutex);
}

void WinCounter::Delete()
{
    delete this;
}

int WinCounter::GetCount()
{
    WaitForSingleObject(hMutex, INFINITE);
    int result = count;
    ReleaseMutex(hMutex);

    return result;
}

void WinCounter::Increment()
{
    WaitForSingleObject(hMutex, INFINITE);
    count++;
    ReleaseMutex(hMutex);
}

void WinCounter::SetCount(int value)
{
    WaitForSingleObject(hMutex, INFINITE);
    count = value;
    ReleaseMutex(hMutex);
}






