#include "log.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstdarg>
#include <memory>
#include <unistd.h> // Thư viện để lấy PID
#include <thread>
#include <pthread.h> 
// Mã màu ANSI
const char* RESET_COLOR = "\033[0m";
const char* INFO_COLOR = "\033[32m";     // Màu xanh lá
const char* WARNING_COLOR = "\033[33m";  // Màu vàng
const char* ERROR_COLOR = "\033[31m";    // Màu đỏ
const char* DEBUG_COLOR = "\033[34m";    // Màu xanh dương

const char* LogLevelToString(LogLevel level) {
    switch (level) {
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        case DEBUG: return "DEBUG";
        default: return "UNKNOWN";
    }
}

std::string GetCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time);
    std::ostringstream oss;
    oss << std::put_time(now_tm, "%H:%M:%S");
    return oss.str();
}

void Log(LogLevel level, const char* function, int line, const std::string &message, const char* tag) {
    const char* color;
    switch (level) {
        case INFO: color = INFO_COLOR; break;
        case WARNING: color = WARNING_COLOR; break;
        case ERROR: color = ERROR_COLOR; break;
        case DEBUG: color = DEBUG_COLOR; break;
        default: color = RESET_COLOR; break;
    }

    pid_t pid = getpid(); // Lấy PID của process
    // std::thread::id this_id = std::this_thread::get_id(); // Lấy thread ID

    std::cout << color
              << "[" << GetCurrentTime() << "]"
              << "[" << LogLevelToString(level) << "]"
              << "[" << tag << "]"
              << "[" << function << ":" << line << "]"
              << "[PID:" << pid << "]"
              << "[TID:" << pthread_self() << "] "
              << message
              << RESET_COLOR << std::endl;
}

std::string FormatString(const char* format, ...) {
    va_list args;
    va_start(args, format);
    size_t size = std::vsnprintf(nullptr, 0, format, args) + 1; // Extra space for '\0'
    va_end(args);

    std::unique_ptr<char[]> buf(new char[size]);
    va_start(args, format);
    std::vsnprintf(buf.get(), size, format, args);
    va_end(args);

    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}