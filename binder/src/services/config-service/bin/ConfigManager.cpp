#include "ConfigManager.h"

ConfigManager::ConfigManager() {
    mReceiverDeathRecipient = new ReceiverDeathRecipient(*this);
    createInternalThread();
}

ConfigManager::~ConfigManager() {
    joinInternalThread();
}

void ConfigManager::instantiate() {
    android::defaultServiceManager()->addService(android::String16(ConfigManager::getServiceName()), new ServiceStub(*this));
}

void ConfigManager::onStart() {
    connectToAppMgr();
}

int32_t ConfigManager::sum(int32_t arg1, int32_t arg2) {
    LOGI("ConfigManager handler api sum()");
    int32_t sum = arg1 + arg2;
    for (uint32_t i = 0; i < mConfigReceiverList.size(); i++) {
        mConfigReceiverList[i]->onConfigDataChanged(sum);
    }
    return sum;
}

bool ConfigManager::registerReceiver(android::sp<IConfigurationManagerReceiver> &receiver) {
    LOGI("ConfigManager handler api registerReceiver()");
    Mutex::Autolock _l(mRegisterLock);

    for (size_t i = 0; i < mConfigReceiverList.size(); i++) {
        if (IInterface::asBinder(mConfigReceiverList[i]) == IInterface::asBinder(receiver)) {
            LOGE("receiver still exists ");
            return false;
        }
    }

    IInterface::asBinder(receiver)->linkToDeath(mReceiverDeathRecipient);
    mConfigReceiverList.add(receiver);

    LOGI("successfully, mConfigReceiverList size:%d ", (int)mConfigReceiverList.size());
    return true;
}

void ConfigManager::onReceiverBinderDied(const android::wp<android::IBinder> &who) {
    LOGD("handle onReceiverBinderDied()");
    Mutex::Autolock _l(mRegisterLock);

    for (size_t i = 0; i < mConfigReceiverList.size(); i++) {
        if (IInterface::asBinder(mConfigReceiverList[i]) == who) {
            mConfigReceiverList.removeAt(i);
            LOGI("mConfigReceiverList size:%d", (int)mConfigReceiverList.size());
            break;
        }
    }
}

void ConfigManager::connectToAppMgr() {
    LOGI("start connnect to Appmgr ");
    if (mAppReceiver == nullptr) mAppReceiver = new appReceiver(*this);
    mAppManager = android::interface_cast<IApplicationManagerService>(android::defaultServiceManager()->getService(android::String16(APP_SRV_NAME)));
    if (mAppManager.get() != nullptr) {
        LOGI("start register mAppReceiver");
        mAppManager->registerReceiver(mAppReceiver);
        android::IInterface::asBinder(mAppManager)->linkToDeath(mReceiverDeathRecipient);

    } else {
        LOGE("Retry to connect to AppMgr Service ");
        // Gửi một số thông điệp từ luồng chính toiws internal thread
        {
            std::lock_guard<std::mutex> lock(queueMutexToInternal);
            messageQueueToInternal.push(MESSAGE_ID::RECONNECT_TO_APPSERVICE);
        }
        conditionVarToInternal.notify_one();
    }
}

int32_t ConfigManager::ServiceStub::sum(int32_t arg1, int32_t arg2) {
    LOGD("arg1: %d ,arg2: %d", arg1, arg2);
    return mParent.sum(arg1, arg2);
}

bool ConfigManager::ServiceStub::registerReceiver(android::sp<IConfigurationManagerReceiver> &receiver) {
    return mParent.registerReceiver(receiver);
}
