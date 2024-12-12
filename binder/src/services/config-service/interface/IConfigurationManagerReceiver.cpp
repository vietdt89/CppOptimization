#define LOG_TAG "IConfigReceiver"

#include "IConfigurationManagerReceiver.h"


class BpConfigurationManagerReceiver : public android::BpInterface<IConfigurationManagerReceiver>
{
public:
    BpConfigurationManagerReceiver(const android::sp<android::IBinder>& impl)
        : BpInterface<IConfigurationManagerReceiver>(impl) { }

    void onConfigDataChanged(int32_t payload)
    {
        LOGI("BpConfigurationManagerReceiver  notify", __func__);

        Parcel data, reply;
        data.writeInterfaceToken(IConfigurationManagerReceiver::getInterfaceDescriptor());
        data.writeInt32(payload);
        remote()->transact(TRANSACT_ONCONFIG_DATA_CHANGED, data, &reply);
    }


};

IMPLEMENT_META_INTERFACE(ConfigurationManagerReceiver, "service_layer.IConfigurationManagerReceiver");

android::status_t BnConfigurationManagerReceiver::onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags)
{
    switch (code)
    {
        case TRANSACT_ONCONFIG_DATA_CHANGED:
        {
            LOGI("BnConfigurationManagerReceiver got the notify from ConfigMgr", __func__);
            CHECK_INTERFACE(IConfigurationManagerReceiver, data, reply);
            int32_t payload = data.readInt32();
            onConfigDataChanged(payload);
            break;
        }
        default:
            break;
    }

    return android::NO_ERROR;
}
