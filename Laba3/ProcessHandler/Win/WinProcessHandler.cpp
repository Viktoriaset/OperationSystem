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
    std::string commandLine = executable + " " + arguments;

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (!CreateProcessA(
            nullptr,
            const_cast<LPSTR>(commandLine.data()),
            nullptr,
            nullptr,
            FALSE,
            0,
            nullptr,
            nullptr,
            &si,
            &pi))
    {
        std::cerr << "Failed to create process. Error: " << GetLastError() << '\n';
    }
    else
    {
        std::string message = "PID: " + std::to_string(pi.dwProcessId) + " DateTime: " + timer->GetDateTime();
        logger->Log(message);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    StartCounterUpscale();
    StartLogging();
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
