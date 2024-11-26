#include "PosixLogger.h"
#include <iostream>
#include <string>
#if !_WIN32
    #include <fcntl.h>
    #include <unistd.h>
#endif

ILogger* PosixLogger::Create()
{
#if !_WIN32
    return new PosixLogger();
#else
    throw std::exception("WinLogger::Create");
#endif
}

void PosixLogger::Log(std::string info)
{
#if !_WIN32
    int fileDescriptor = open(filePath.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fileDescriptor == -1) {
        throw std::runtime_error("Error opening file");
    }

    // Запись данных в файл
    ssize_t bytesWritten = write(fileDescriptor, info.c_str(), info.size());
    if (bytesWritten == -1) {
        std::cerr << "Ошибка записи в файл" << std::endl;
        close(fileDescriptor);
    }

    // Закрытие файла
    close(fileDescriptor);
#endif
}
