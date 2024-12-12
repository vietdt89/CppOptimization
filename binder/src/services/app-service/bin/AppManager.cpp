#include "AppManager.h"

AppManager::AppManager() {
    mReceiverDeathRecipient = new ReceiverDeathRecipient(*this);
    createInternalThread();
}

AppManager::~AppManager() {
    joinInternalThread();
}

void AppManager::instantiate() {
    android::defaultServiceManager()->addService(android::String16(AppManager::getServiceName()), new ServiceStub(*this));
}

void AppManager::onStart() {
    // if you run binary as a service you need to comment this line
    // connectToConfigMgr();
}

int32_t AppManager::sum(int32_t arg1, int32_t arg2) {
    LOGI("AppManager handler api sum()");
    int32_t sum = arg1 + arg2;
    for (uint32_t i = 0; i < mAppReceiverList.size(); i++) {
        mAppReceiverList[i]->onAppMgrNotify(sum);
    }
     std::this_thread::sleep_for(std::chrono::seconds(60));
    return sum;
}

bool AppManager::registerReceiver(android::sp<IApplicationManagerReceiver> &receiver) {
    LOGI("AppManager handler api registerReceiver()");
    Mutex::Autolock _l(mRegisterLock);

    for (size_t i = 0; i < mAppReceiverList.size(); i++) {
        if (IInterface::asBinder(mAppReceiverList[i]) == IInterface::asBinder(receiver)) {
            LOGE("receiver still exists");
            return false;
        }
    }

    IInterface::asBinder(receiver)->linkToDeath(mReceiverDeathRecipient);
    mAppReceiverList.add(receiver);

    LOGI("successfully, mAppReceiverList size:%d ", (int)mAppReceiverList.size());
    return true;
}

void AppManager::onReceiverBinderDied(const android::wp<android::IBinder> &who) {
    LOGD("handle onReceiverBinderDied()");
    Mutex::Autolock _l(mRegisterLock);

    for (size_t i = 0; i < mAppReceiverList.size(); i++) {
        if (IInterface::asBinder(mAppReceiverList[i]) == who) {
            mAppReceiverList.removeAt(i);
            LOGI("mAppReceiverList size:%d", (int) mAppReceiverList.size());
            break;
        }
    }
}

void AppManager::connectToConfigMgr() {
    LOGI("start connnect to ConfigMgr ");
    if (mConfigManager == nullptr) {
        LOGI("create instance for mConfigReceiver ");
        mConfigReceiver = new configReceiver(*this);
    }
    mConfigManager = android::interface_cast<IConfigurationManagerService>(android::defaultServiceManager()->getService(android::String16(CONFIG_SRV_NAME)));
    if (mConfigManager.get() != nullptr) {
        LOGI("start register mConfigManager");
        bool result = mConfigManager->registerReceiver(mConfigReceiver);
        if (result) {
            LOGI("register mConfigManager successfully ");
            android::IInterface::asBinder(mConfigManager)->linkToDeath(mReceiverDeathRecipient);
        }
    } else {
        LOGE("mConfigManager is null, retry... ");
        // Gửi một số thông điệp từ luồng chính toiws internal thread
        {
            std::lock_guard<std::mutex> lock(queueMutexToInternal);
            messageQueueToInternal.push(MESSAGE_ID::RECONNECT_TO_CONFIGSERVICE);
        }
        conditionVarToInternal.notify_one();
    }
}

int32_t AppManager::ServiceStub::sum(int32_t arg1, int32_t arg2) {
    LOGD("arg1: %d ,arg2: %d", arg1, arg2);
    return mParent.sum(arg1, arg2);
}

bool AppManager::ServiceStub::registerReceiver(android::sp<IApplicationManagerReceiver> &receiver) {
    return mParent.registerReceiver(receiver);
}
