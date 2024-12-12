#ifndef IApplication_MANAGER_RECEIVER_H
#define IApplication_MANAGER_RECEIVER_H
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
#include "log.h"
using namespace android;

class IApplicationManagerReceiver : public android::IInterface
{
public:
    enum
    {
        TRANSACT_APPMGR_NOTIFY = IBinder::FIRST_CALL_TRANSACTION,
    };

	DECLARE_META_INTERFACE(ApplicationManagerReceiver);
	virtual void onAppMgrNotify(int32_t payload) = 0;

};

class BnApplicationManagerReceiver : public BnInterface<IApplicationManagerReceiver>
{
public:
	virtual android::status_t onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags = 0);
};

#endif /*IAPPLICATION_MANAGER_RECEIVER_H*/
