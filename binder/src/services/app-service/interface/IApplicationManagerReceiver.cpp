#define LOG_TAG "IAppReceiver"
#include "IApplicationManagerReceiver.h"

class BpApplicationManagerReceiver : public android::BpInterface<IApplicationManagerReceiver>
{
public:
    BpApplicationManagerReceiver(const android::sp<android::IBinder>& impl)
        : BpInterface<IApplicationManagerReceiver>(impl) { }

    void onAppMgrNotify(int32_t payload)
    {
        LOGI("BpApplicationManagerReceiver::  notify", __func__);

        Parcel data, reply;
        data.writeInterfaceToken(IApplicationManagerReceiver::getInterfaceDescriptor());
        data.writeInt32(payload);
        remote()->transact(TRANSACT_APPMGR_NOTIFY, data, &reply);
    }


};

IMPLEMENT_META_INTERFACE(ApplicationManagerReceiver, "service_layer.IApplicationManagerReceiver");

android::status_t BnApplicationManagerReceiver::onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags)
{
    switch (code)
    {
        case TRANSACT_APPMGR_NOTIFY:
        {
            LOGI("BnApplicationManagerReceiver:: got the notify from AppMgr", __func__);
            CHECK_INTERFACE(IApplicationManagerReceiver, data, reply);
            int32_t payload = data.readInt32();
            onAppMgrNotify(payload);
            break;
        }
        default:
            break;
    }

    return android::NO_ERROR;
}
