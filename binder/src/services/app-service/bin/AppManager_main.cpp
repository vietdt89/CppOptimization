#include <unistd.h>
#include <iostream>
#include "log.h"
#include "AppManager.h"

int main(int argc, char** argv) {
    LOGD("AppManager: main - running....");
    AppManager* service = new AppManager();
    service->instantiate();

    // Cài đặt số luồng tối đa trong ThreadPool
    ProcessState::self()->setThreadPoolMaxThreadCount(3);
    // Khởi tạo pool các luồng để xử lý các yêu cầu IPC
    ProcessState::self()->startThreadPool();

    // Thông báo tới StartD: AppMgr đã sẵn sàng
    service->onStart();

    // Tham gia vào pool các luồng và bắt đầu xử lý các yêu cầu IPC
    IPCThreadState::self()->joinThreadPool();
        // while(true) {
    //     std::cout << "hello world" << std::endl;
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }
    return 0;
}
