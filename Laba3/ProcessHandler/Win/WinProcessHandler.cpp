#pragma once
#include "WinProcessHandler.h"

#include <iostream>
#include <Windows.h>

WinProcessHandler::WinProcessHandler(ILogger *logger, ICounter *counter, ITimer *timer)
{
    this->logger = logger;
    this->counter = counter;
    this->timer = timer;
}

void WinProcessHandler::StartLogging()
{
    while (true)
    {
        std::string message = timer->GetDateTime() + " | "
        + std::to_string(GetCurrentProcessId()) + " | "
        + std::to_string(counter->GetCount());
        logger->Log(message);
        timer->Sleep(1);
    }
}

void WinProcessHandler::StartCounterUpscale()
{
    while (true)
    {
        counter->Increment();
        timer->Sleep(0, 300);
    }
}

void WinProcessHandler::Delete()
{
    delete this;
}

void WinProcessHandler::CreateCrossPlatformProcess(const std::string& executable, const std::string& arguments)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    if (!CreateProcess(
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            FALSE,
            0,
            nullptr,
            nullptr,
            LPSTARTUPINFOW(&si),
            &pi))
    {
        std::cerr << "Failed to create process. Error: " << GetLastError() << '\n';
    }
    else
    {
        StartCounterUpscale();
        StartLogging();

        WaitForSingleObject(pi.hProcess, INFINITE);
        
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

WinProcessHandler::~WinProcessHandler()
= default;


void WinProcessHandler::SetCount(int value)
{
    this->counter->SetCount(value);
}

auto WinProcessHandler::Create(ILogger* logger, ICounter* counter, ITimer* timer) -> IProcessHandler*
{
    return new WinProcessHandler(logger, counter, timer);
}
