#include <unistd.h>

#include <iostream>

#include "ConfigManager.h"
#include "IApplicationManagerService.h"
#include "IApplicationManagerServiceTypes.h"

int main(int argc, char** argv) {
    LOGD("ConfigManager: main - running....");
    ConfigManager* service = new ConfigManager();
    service->instantiate();

    // Khởi tạo pool các luồng để xử lý các yêu cầu IPC
    ProcessState::self()->startThreadPool();
    service->onStart();

    // Tham gia vào pool các luồng và bắt đầu xử lý các yêu cầu IPC
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
