#ifndef IAPPLICATION_MANAGER_SERVICE_H
#define IAPPLICATION_MANAGER_SERVICE_H
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
#include "IApplicationManagerReceiver.h"

using namespace android;

class IApplicationManagerService : public IInterface
{
public:
    enum
    {
        TRANSACTION_SUM = IBinder::FIRST_CALL_TRANSACTION,
        TRANSACTION_registerReceiver,
    };

	DECLARE_META_INTERFACE(ApplicationManagerService);
	virtual int32_t sum(int32_t arg1, int32_t arg2) = 0;
    virtual bool registerReceiver(android::sp<IApplicationManagerReceiver>& receiver) = 0;

};

class BnApplicationManagerService : public BnInterface<IApplicationManagerService>
{
public:
	virtual android::status_t onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags = 0);
};

#endif /*IAPPLICATION_MANAGER_SERVICE_H*/
