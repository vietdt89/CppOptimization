#define LOG_TAG "IConfigService"
#include "IConfigurationManagerService.h"

class BpConfigurationManagerService : public android::BpInterface<IConfigurationManagerService> {
   public:
    BpConfigurationManagerService(const android::sp<android::IBinder> &impl) : BpInterface<IConfigurationManagerService>(impl) {}

    int32_t sum(int32_t arg1, int32_t arg2) {
        LOGI("BpConfigurationManagerService::%s send request", __func__);

        LOGI("data will be sent: arg1: %d, arg2: %d", arg1, arg2);
        Parcel data, reply;
        data.writeInterfaceToken(IConfigurationManagerService::getInterfaceDescriptor());
        data.writeInt32(arg1);
        data.writeInt32(arg2);

        android::status_t status =  remote()->transact(IConfigurationManagerService::TRANSACTION_SUM, data, &reply);
        LOGI("BpConfigurationManagerService::sum transact reply");

        int32_t res;
        (void)reply.readInt32(&res);
        LOGI("BpConfigurationManagerService reply %i + %i = %i (status: %i) ", arg1, arg2, res, status);
        return res;
    }

    bool registerReceiver(android::sp<IConfigurationManagerReceiver> &receiver) {
        LOGI("BpConfigurationManagerService::%s send request", __func__);
        if (receiver == nullptr) {
            ALOGE("An error occurred while processing registration request: invalid receiver");
            return false;
        }

        android::Parcel data;
        android::Parcel reply;

        (void)data.writeInterfaceToken(IConfigurationManagerService::getInterfaceDescriptor());
        (void)data.writeStrongBinder(android::IInterface::asBinder(receiver));

        (void)remote()->transact(TRANSACTION_registerReceiver, data, &reply);
        return static_cast<bool>(reply.readInt32());
    }
};

IMPLEMENT_META_INTERFACE(ConfigurationManagerService, "service_layer.IConfigurationManagerService");

android::status_t BnConfigurationManagerService::onTransact(uint32_t code, const Parcel &data, Parcel* reply, uint32_t flags) {
    switch (code) {
        case TRANSACTION_SUM : {
            LOGI("BnConfigurationManagerService::%s got request sum", __func__);
            CHECK_INTERFACE(IConfigurationManagerService, data, reply);
            int32_t arg1 = data.readInt32();
            int32_t arg2 = data.readInt32();

            int32_t value = sum(arg1, arg2);
            reply->writeInt32(value);
            break;
        }
        case TRANSACTION_registerReceiver : {
            LOGI("BnConfigurationManagerService::%s got request registerReceiver", __func__);
            CHECK_INTERFACE(IConfigurationManagerService, data, reply);
            android::sp<IConfigurationManagerReceiver> receiver = android::interface_cast<IConfigurationManagerReceiver>(data.readStrongBinder());
            error_t result = registerReceiver(receiver);
            (void)reply->writeInt32(result);
            break;
        }
        default :
            break;
    }

    return android::NO_ERROR;
}
