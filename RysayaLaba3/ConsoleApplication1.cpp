#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#include <process.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#endif

int counter = 0;
bool is_logging_program = false;
bool can_spawn_copies = true;

void log_message(const std::string& message) {
#ifdef _WIN32
    HANDLE hFile = CreateFile(reinterpret_cast<LPCWSTR>("log.txt"), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        SetFilePointer(hFile, 0, NULL, FILE_END);
        DWORD written;
        WriteFile(hFile, message.c_str(), message.size(), &written, NULL);
        WriteFile(hFile, "\n", 1, &written, NULL);
        CloseHandle(hFile);
    }
#else
    FILE* log_file = fopen("log.txt", "a");
    if (log_file) {
        fprintf(log_file, "%s\n", message.c_str());
        fclose(log_file);
    }
#endif
}

std::string get_current_time() {
#ifdef _WIN32
    SYSTEMTIME st;
    GetLocalTime(&st);
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d.%03d",
             st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    return std::string(buffer);
#else
    struct timespec ts;
    struct tm tm_info;
    clock_gettime(CLOCK_REALTIME, &ts);
    localtime_r(&ts.tv_sec, &tm_info);
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d.%03ld",
             tm_info.tm_year + 1900, tm_info.tm_mon + 1, tm_info.tm_mday,
             tm_info.tm_hour, tm_info.tm_min, tm_info.tm_sec, ts.tv_nsec / 1000000);
    return std::string(buffer);
#endif
}

void copy_behavior_1() {
#ifdef _WIN32
    int pid = _getpid();
#else
    int pid = getpid();
#endif
    log_message("Copy 1 started. PID: " + std::to_string(pid) + ", Time: " + get_current_time());
    counter += 10;
    log_message("Copy 1 exiting. PID: " + std::to_string(pid) + ", Time: " + get_current_time());
}

void copy_behavior_2() {
#ifdef _WIN32
    int pid = _getpid();
#else
    int pid = getpid();
#endif
    log_message("Copy 2 started. PID: " + std::to_string(pid) + ", Time: " + get_current_time());
    counter *= 2;
#ifdef _WIN32
    Sleep(2000);
#else
    sleep(2);
#endif
    counter /= 2;
    log_message("Copy 2 exiting. PID: " + std::to_string(pid) + ", Time: " + get_current_time());
}

void spawn_copies() {
    static bool copy1_running = false;
    static bool copy2_running = false;

    if (!copy1_running && !copy2_running) {
        copy1_running = true;
        copy2_running = true;

#ifdef _WIN32
        _beginthread([](void*) {
            copy_behavior_1();
            copy1_running = false;
        }, 0, nullptr);

        _beginthread([](void*) {
            copy_behavior_2();
            copy2_running = false;
        }, 0, nullptr);
#else
        if (fork() == 0) {
            copy_behavior_1();
            exit(0);
        }
        if (fork() == 0) {
            copy_behavior_2();
            exit(0);
        }
#endif
    } else {
        log_message("Copies not spawned. Another instance is still running.");
    }
}

void logging_task() {
#ifdef _WIN32
    int pid = _getpid();
#else
    int pid = getpid();
#endif
    while (true) {
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
        log_message("PID: " + std::to_string(pid) + ", Time: " + get_current_time() + ", Counter: " + std::to_string(counter));
    }
}

void counter_task() {
    while (true) {
#ifdef _WIN32
        Sleep(300);
#else
        usleep(300000);
#endif
        ++counter;
    }
}

int main() {
#ifdef _WIN32
    int pid = _getpid();
#else
    int pid = getpid();
#endif
    log_message("Program started. PID: " + std::to_string(pid) + ", Time: " + get_current_time());

#ifdef _WIN32
    _beginthread([](void*) { counter_task(); }, 0, nullptr);
#else
    if (fork() == 0) {
        counter_task();
        exit(0);
    }
#endif

    if (!is_logging_program) {
        is_logging_program = true;
#ifdef _WIN32
        _beginthread([](void*) { logging_task(); }, 0, nullptr);
#else
        if (fork() == 0) {
            logging_task();
            exit(0);
        }
#endif

        while (true) {
#ifdef _WIN32
            Sleep(3000);
#else
            sleep(3);
#endif
            if (can_spawn_copies) {
                spawn_copies();
            }
        }
    } else {
        while (true) {
            std::cout << "Enter new counter value: ";
            std::string input;
            std::cin >> input;
            try {
                counter = std::stoi(input);
            } catch (...) {
                std::cout << "Invalid input. Try again." << std::endl;
            }
        }
    }

    return 0;
}
