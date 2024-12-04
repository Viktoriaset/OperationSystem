#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#endif

std::vector<float> hourly_temperatures;
float daily_sum = 0;
int daily_count = 0;

void log_message(const std::string& filename, const std::string& message) {
#ifdef _WIN32
    HANDLE hFile = CreateFile(reinterpret_cast<LPCWSTR>(filename.c_str()), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        SetFilePointer(hFile, 0, NULL, FILE_END);
        DWORD written;
        WriteFile(hFile, message.c_str(), message.size(), &written, NULL);
        WriteFile(hFile, "\n", 1, &written, NULL);
        CloseHandle(hFile);
    }
#else
    FILE* log_file = fopen(filename.c_str(), "a");
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
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d",
             st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
    return std::string(buffer);
#else
    time_t now = time(NULL);
    struct tm tm_info;
    localtime_r(&now, &tm_info);
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d",
             tm_info.tm_year + 1900, tm_info.tm_mon + 1, tm_info.tm_mday,
             tm_info.tm_hour, tm_info.tm_min, tm_info.tm_sec);
    return std::string(buffer);
#endif
}

float simulate_temperature_reading() {
#ifdef _WIN32
    // Simulating USB interaction by generating a random temperature
    HANDLE hComm = CreateFile(reinterpret_cast<LPCWSTR>("COM3"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hComm == INVALID_HANDLE_VALUE) {
        return static_cast<float>(rand() % 500) / 10.0f - 10.0f; // Fallback to random
    }

    char buffer[10] = {0};
    DWORD bytesRead;
    ReadFile(hComm, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
    CloseHandle(hComm);
    return std::stof(buffer);
#else
    // Simulating USB interaction by generating a random temperature
    int fd = open("/dev/ttyUSB0", O_RDONLY | O_NOCTTY);
    if (fd == -1) {
        return static_cast<float>(rand() % 500) / 10.0f - 10.0f; // Fallback to random
    }

    char buffer[10] = {0};
    read(fd, buffer, sizeof(buffer) - 1);
    close(fd);
    return std::stof(buffer);
#endif
}

void record_temperature() {
    float temperature = simulate_temperature_reading();
    hourly_temperatures.push_back(temperature);
    daily_sum += temperature;
    daily_count++;
    log_message("temperature_log.txt", get_current_time() + ", " + std::to_string(temperature));
}

void calculate_hourly_average() {
    if (!hourly_temperatures.empty()) {
        float sum = 0;
        for (float temp : hourly_temperatures) {
            sum += temp;
        }
        float average = sum / hourly_temperatures.size();
        log_message("hourly_avg_log.txt", get_current_time() + ", " + std::to_string(average));
        hourly_temperatures.clear();
    }
}

void calculate_daily_average() {
    if (daily_count > 0) {
        float average = daily_sum / daily_count;
        log_message("daily_avg_log.txt", get_current_time() + ", " + std::to_string(average));
        daily_sum = 0;
        daily_count = 0;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    while (true) {
        record_temperature();
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif

        static int seconds = 0;
        seconds++;
        if (seconds % 3600 == 0) {
            calculate_hourly_average();
        }
        if (seconds % 86400 == 0) {
            calculate_daily_average();
        }
    }

    return 0;
}
