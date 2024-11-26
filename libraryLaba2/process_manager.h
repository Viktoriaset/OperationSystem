#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <string>

class ProcessManager {
public:
    ProcessManager();
    ~ProcessManager();

    // Запускает программу в фоновом режиме
    bool startProcess(const std::string& command);

    // Ожидает завершения программы и возвращает код выхода
    int waitForProcess();

private:
    void* processHandle; // Платформозависимая структура для хранения информации о процессе
};

#endif // PROCESS_MANAGER_H
