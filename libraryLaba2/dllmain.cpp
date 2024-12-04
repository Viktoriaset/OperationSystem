#include "process_manager.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <string>
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#endif

ProcessManager::ProcessManager() : processHandle(nullptr) {}

ProcessManager::~ProcessManager() {
#ifdef _WIN32
    if (processHandle) {
        CloseHandle((HANDLE)processHandle);
    }
#else
    if (processHandle) {
        // Платформозависимая очистка
    }
#endif
}

bool ProcessManager::startProcess(const std::string& command) {
#ifdef _WIN32
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Запускаем процесс
    if (!CreateProcess(NULL, reinterpret_cast<LPWSTR>(const_cast<char*>(command.c_str())), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        return false;
    }
    processHandle = (void*)pi.hProcess;
#else
    pid_t pid = fork();
    if (pid == 0) {
        // Дочерний процесс
        char* args[] = {const_cast<char*>("/bin/sh"), const_cast<char*>("-c"), const_cast<char*>(command.c_str()), NULL};
        execvp(args[0], args);
        exit(EXIT_FAILURE); // execvp не должен вернуться, если все прошло успешно
    }
    processHandle = (void*)(intptr_t)pid; // сохраняем PID
#endif
    return true;
}

int ProcessManager::waitForProcess() {
#ifdef _WIN32
    WaitForSingleObject((HANDLE)processHandle, INFINITE);
    DWORD exitCode;
    GetExitCodeProcess((HANDLE)processHandle, &exitCode);
    return exitCode;
#else
    int status;
    waitpid((pid_t)(intptr_t)processHandle, &status, 0);
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return -1; // Ошибка
#endif
}
