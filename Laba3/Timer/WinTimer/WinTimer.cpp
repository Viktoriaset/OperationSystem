#include "WinTimer.h"
#include <Windows.h>
#include <ctime>

ITimer* WinTimer::Create()
{
#ifdef _WIN32
    return new WinTimer();
#else
    throw new std::exception("WinTimer::Create");
#endif
}

WinTimer::WinTimer() = default;

WinTimer::~WinTimer() = default;

void WinTimer::Delete()
{
    
}

time_t WinTimer::Time()
{
    return time(nullptr);
}

void WinTimer::Sleep(int seconds, int milliseconds)
{
    Sleep(seconds * 1000 + milliseconds);
}

std::string WinTimer::GetDateTime()
{
    LPSYSTEMTIME lpSystemTime = new SYSTEMTIME();
    GetSystemTime(lpSystemTime);

    std::string dateTime;
    dateTime.append(std::to_string(lpSystemTime->wYear));
    dateTime.append(".");
    dateTime.append(std::to_string(lpSystemTime->wMonth));
    dateTime.append(".");
    dateTime.append(std::to_string(lpSystemTime->wDay));
    dateTime.append(" ");
    dateTime.append(std::to_string(lpSystemTime->wHour));
    dateTime.append(":");
    dateTime.append(std::to_string(lpSystemTime->wMinute));
    dateTime.append(":");
    dateTime.append(std::to_string(lpSystemTime->wSecond));
    dateTime.append("::");
    dateTime.append(std::to_string(lpSystemTime->wMilliseconds));

    return dateTime;
}



