#include "WinLogger.h"

#include <iostream>
#include <Windows.h>

ILogger* WinLogger::Create()
{
#ifdef _WIN32
    return new WinLogger();
#else
    throw new std::exception("WinLogger::Create");
#endif
}

WinLogger::WinLogger()
{
    File = CreateFile(GetLogFileName(FileName).c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
    nullptr);

    if(INVALID_HANDLE_VALUE == File) {
        throw std::exception("WinLogger::Create");
    }
}

WinLogger::~WinLogger()
{
    CloseHandle(File);
}


void WinLogger::Delete()
{
    delete this;
}

void WinLogger::Log(std::string info)
{
    info.append("\n");
    DWORD bytesWritten;
    BOOL result = WriteFile(
        File,
        info.c_str(),            // Указатель на данные строки
        info.size(),              // Размер данных в байтах
        &bytesWritten,
        NULL
    );

    if (!result) {
        std::cerr << "Ошибка записи в файл: " << GetLastError() << std::endl;
        throw std::exception("WriteFile");
    }
}

std::wstring WinLogger::GetLogFileName(std::string fileName)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, fileName.c_str(), -1, NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, fileName.c_str(), -1, &wstrTo[0], size_needed);
    return wstrTo;
}


