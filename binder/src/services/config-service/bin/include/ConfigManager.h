/**
 * @copyright
 * Copyright (c) 2015 by LG Electronics Inc.
 * This program or software including the accompanying associated documentation
 * ("Software") is the proprietary software of LG Electronics Inc. and or its
 * licensors, and may only be used, duplicated, modified or distributed pursuant
 * to the terms and conditions of a separate written license agreement between you
 * and LG Electronics Inc. ("Authorized License"). Except as set forth in an
 * Authorized License, LG Electronics Inc. grants no license (express or implied),
 * rights to use, or waiver of any kind with respect to the Software, and LG
 * Electronics Inc. expressly reserves all rights in and to the Software and all
 * intellectual property therein. If you have no Authorized License, then you have
 * no rights to use the Software in any ways, and should immediately notify LG
 * Electronics Inc. and discontinue all use of the Software.
 * @file        ConfigManager.h
 * @brief       class for ConfigurationManagerService
 * @author
 *    copyright (c) 2018  Jaeho Choi <elliott.choi@lge.com>
 * @version     1.0.00
 */

#ifndef SERVICELAYER_CONFIG_MANAGER_SERVICE_H
#define SERVICELAYER_CONFIG_MANAGER_SERVICE_H

/* Standard library */
#include <unistd.h>
#include <utils/Mutex.h>

#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

#include "log.h"
#include "IApplicationManagerReceiver.h"
#include "IApplicationManagerService.h"
#include "IApplicationManagerServiceTypes.h"
#include "IConfigurationManagerReceiver.h"
#include "IConfigurationManagerService.h"

#define LOG_TAG "ConfigManager"

class ConfigManager {
   public:
    enum MESSAGE_ID : uint8_t {
        RECONNECT_TO_APPSERVICE = 0x01,
    };

    ConfigManager();
    virtual ~ConfigManager();
    void instantiate();
    void onStart();

    int32_t sum(int32_t arg1, int32_t arg2);
    bool registerReceiver(android::sp<IConfigurationManagerReceiver> &receiver);
    void connectToAppMgr();

   private:
    void onReceiverBinderDied(const android::wp<android::IBinder> &who);
    static const char* getServiceName() { return "service_layer.ConfigurationManagerService"; };

   private:
    class ServiceStub : public BnConfigurationManagerService {
       public:
        ServiceStub(ConfigManager &parent) : mParent(parent) {}
        int32_t sum(int32_t arg1, int32_t arg2) override;
        bool registerReceiver(android::sp<IConfigurationManagerReceiver> &receiver) override;

       private:
        ConfigManager &mParent;
    };

    // Tạo class để nhận thông báo khi receiver chết
    class ReceiverDeathRecipient : public android::IBinder::DeathRecipient {
       public:
        ReceiverDeathRecipient(ConfigManager &parent) : mParent(parent) {}
        virtual ~ReceiverDeathRecipient() {}
        virtual void binderDied(const android::wp<android::IBinder> &who) {
            mParent.onReceiverBinderDied(who);
        }

       private:
        ConfigManager &mParent;
    };

    // Tạo lớp appReceiver để nhận notify từ Config Manager
    class appReceiver : public BnApplicationManagerReceiver {
       public:
        appReceiver(ConfigManager &me) : mParent(me) {};
        virtual ~appReceiver() {};
        virtual void onAppMgrNotify(int32_t payload) override {
            LOGI("onAppMgrNotify payload: %d ", payload);
            return;
        }

       private:
        ConfigManager &mParent;
    };

   private:
    // Create a vector to store all instances of receiver
    android::Vector<android::sp<IConfigurationManagerReceiver>> mConfigReceiverList;
    // Tạo một đối tượng lắng nghe sự kiện onBinderDied từ các receiver
    android::sp<ReceiverDeathRecipient> mReceiverDeathRecipient = nullptr;

    // tạo đối tượng để giao tiếp và nhận sự kiện từ application manager
    android::sp<IApplicationManagerReceiver> mAppReceiver;
    android::sp<IApplicationManagerService> mAppManager;

    mutable Mutex mRegisterLock;
    std::thread internalThread;

    // Queue để lưu trữ các thông điệp từ internalThread đến IPC thread
    std::queue<uint8_t> messageQueueToInternal;
    std::mutex queueMutexToInternal;
    std::condition_variable conditionVarToInternal;

    // Create internal handler message
    // Hàm sẽ được chạy trong thread mới
    void threadhandlerFunction() {
        while (true) {
            std::unique_lock<std::mutex> lock(queueMutexToInternal);
            conditionVarToInternal.wait(lock, [&] { return !messageQueueToInternal.empty(); });

            // Lấy thông điệp từ queue
            uint8_t msg_id = messageQueueToInternal.front();
            messageQueueToInternal.pop();
            lock.unlock();

            // Xử lý thông điệp
            LOGI("InternalThread nhận được thông điệp: 0x%02x ", msg_id);
            switch (static_cast<MESSAGE_ID>(msg_id)) {
                case MESSAGE_ID::RECONNECT_TO_APPSERVICE : {
                    connectToAppMgr();
                    break;
                }
                default :
                    break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void createInternalThread() {
        // Tạo một thread mới chạy song song
        internalThread = std::thread(std::bind(&ConfigManager::threadhandlerFunction, this));
    }
    void joinInternalThread() {
        // Đảm bảo thread mới được join trước khi kết thúc chương trình
        LOGI("join internal thread");
        internalThread.join();
    }
};

#endif  // SERVICELAYER_CONFIG_MANAGER_SERVICE_H
