#define LOG_TAG "IAppService"
#include "IApplicationManagerService.h"

class BpApplicationManagerService : public android::BpInterface<IApplicationManagerService> {
   public:
    BpApplicationManagerService(const android::sp<android::IBinder> &impl) : BpInterface<IApplicationManagerService>(impl) {}

    int32_t sum(int32_t arg1, int32_t arg2) {
        LOGI("BpApplicationManagerService:: send request", __func__);

        LOGI("data will be sent: arg1: %d, arg2: %d", arg1, arg2);
        Parcel data, reply;
        data.writeInterfaceToken(IApplicationManagerService::getInterfaceDescriptor());
        data.writeInt32(arg1);
        data.writeInt32(arg2);

        android::status_t status = remote()->transact(TRANSACTION_SUM, data, &reply);
        LOGI("BpApplicationManagerService::sum transact reply");

        int32_t res;
        (void) reply.readInt32(&res);
        LOGI("BpApplicationManagerService reply %i + %i = %i (status: %i) ", arg1, arg2, res, status);
        return res;
    }

    bool registerReceiver(android::sp<IApplicationManagerReceiver> &receiver) {
        LOGI("BpApplicationManagerService:: send request ", __func__);
        if (receiver == nullptr) {
            ALOGE("An error occurred while processing registration request: invalid receiver");

            return false;
        }

        android::Parcel data;
        android::Parcel reply;

        (void)data.writeInterfaceToken(IApplicationManagerService::getInterfaceDescriptor());
        (void)data.writeStrongBinder(android::IInterface::asBinder(receiver));

        (void)remote()->transact(TRANSACTION_registerReceiver, data, &reply);
        return static_cast<bool>(reply.readInt32());
    }
};

IMPLEMENT_META_INTERFACE(ApplicationManagerService, "service_layer.IApplicationManagerService");

android::status_t BnApplicationManagerService::onTransact(uint32_t code, const Parcel &data, Parcel* reply, uint32_t flags) {
    switch (code) {
        case TRANSACTION_SUM : {
            LOGI("BnApplicationManagerService:: got the client sum", __func__);
            CHECK_INTERFACE(IApplicationManagerService, data, reply);
            int32_t arg1 = data.readInt32();
            int32_t arg2 = data.readInt32();

            int32_t value = sum(arg1, arg2);
            reply->writeInt32(value);
            break;
        }
        case TRANSACTION_registerReceiver : {
            LOGI("BnApplicationManagerService:: got request registerReceiver", __func__);
            CHECK_INTERFACE(IApplicationManagerService, data, reply);
            android::sp<IApplicationManagerReceiver> receiver = android::interface_cast<IApplicationManagerReceiver>(data.readStrongBinder());
            error_t result = registerReceiver(receiver);
            (void)reply->writeInt32(result);
            break;
        }
        default :
            break;
    }

    return android::NO_ERROR;
}
