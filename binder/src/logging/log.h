#ifndef LOG_H
#define LOG_H

#include <string>

// Định nghĩa các mức độ log
enum LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

// Hàm chuyển đổi LogLevel thành chuỗi
const char* LogLevelToString(LogLevel level);

// Hàm lấy thời gian hiện tại dưới dạng chuỗi
std::string GetCurrentTime();

// Hàm log chính
void Log(LogLevel level, const char* function, int line, const std::string& message, const char* tag);

// Kiểm tra và định nghĩa LOG_TAG nếu chưa được định nghĩa
#ifndef LOG_TAG
#define LOG_TAG "LOG_H"
#endif

// Macro để đơn giản hóa việc gọi hàm log
#define LOG(level, message, ...) Log(level, __FUNCTION__, __LINE__, FormatString(message, ##__VA_ARGS__), LOG_TAG)

// Các macro cụ thể cho từng mức độ log
#define LOGI(message, ...) LOG(INFO, message, ##__VA_ARGS__)
#define LOGW(message, ...) LOG(WARNING, message, ##__VA_ARGS__)
#define LOGE(message, ...) LOG(ERROR, message, ##__VA_ARGS__)
#define LOGD(message, ...) LOG(DEBUG, message, ##__VA_ARGS__)

// Hàm định dạng chuỗi
std::string FormatString(const char* format, ...);

#endif // LOG_H