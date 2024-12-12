#ifndef ICONFIGURATION_MANAGER_SERVICE_H
#define ICONFIGURATION_MANAGER_SERVICE_H
#include <stdio.h>
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <string>
#include "IConfigurationManagerReceiver.h"

using namespace android;

class IConfigurationManagerService : public IInterface
{
public:
    enum
    {
        TRANSACTION_SUM = IBinder::FIRST_CALL_TRANSACTION,
        TRANSACTION_registerReceiver,
    };

	DECLARE_META_INTERFACE(ConfigurationManagerService);
	virtual int32_t sum(int32_t arg1, int32_t arg2) = 0;
    virtual bool registerReceiver(android::sp<IConfigurationManagerReceiver>& receiver) = 0;

};

class BnConfigurationManagerService : public BnInterface<IConfigurationManagerService>
{
public:
	virtual android::status_t onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags = 0);
};

#endif /*ICONFIGURATION_MANAGER_SERVICE_H*/
