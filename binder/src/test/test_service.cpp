#include <iostream>

// include file interface config
#include "IConfigurationManagerService.h"
#include "IConfigurationManagerServiceTypes.h"

// include file interface appMgr
#include "IApplicationManagerService.h"
#include "IApplicationManagerServiceTypes.h"

int main() {
    // Tạo đối tượng cho interface config và appMgr
    android::sp<IConfigurationManagerService> configManger = android::interface_cast<IConfigurationManagerService>(android::defaultServiceManager()->getService(String16(CONFIG_SRV_NAME)));

    android::sp<IApplicationManagerService> appManger = android::interface_cast<IApplicationManagerService>(android::defaultServiceManager()->getService(String16(APP_SRV_NAME)));

    if (configManger == nullptr) {
        printf("ConfigMgr is null return E_ERROR \n");
        return 0;
    }
    if (appManger == nullptr) {
        printf("appManger is null return E_ERROR \n");
        return 0;
    }

    int choice = 1;

    while (choice) {
        std::cout << "\n \n";
        std::cout << "Test service start" << std::endl;
        std::cout << "1 - send request to ConfigMgr : " << std::endl;
        std::cout << "2 - send request to AppManager : " << std::endl;
        std::cout << "0 - exit : " << std::endl;
        std::cout << "\n";
        std::cout << "choice option : " << std::endl;
        std::cin >> choice;
        switch (choice) {
            case 0 : {
                break;
            }
            case 1 : {
                int32_t arg1;
                int32_t arg2;
                std::cout << "Input argument : " << std::endl;
                std::cout << "Arg1 = ";
                std::cin >> arg1;
                std::cout << "Arg2 = ";
                std::cin >> arg2;
                int32_t value = configManger->sum(arg1, arg2);
                std::cout << "Sum value response from configManager: " << value << std::endl;
                choice = 1;
                break;
            }
            case 2 : {
                int32_t arg1;
                int32_t arg2;
                std::cout << "Input argument : " << std::endl;
                std::cout << "Arg1 = ";
                std::cin >> arg1;
                std::cout << "Arg2 = ";
                std::cin >> arg2;

                int32_t value = appManger->sum(arg1, arg2);
                std::cout << "Sum value return from appManager: " << value << std::endl;
                choice = 1;
                break;
            }
            default :
                break;
        }
    }
    return 0;
}
