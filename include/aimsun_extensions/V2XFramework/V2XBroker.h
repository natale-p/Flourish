//-*-Mode: C++;-*-
#pragma once

#include "V2XFrameworkUtil.h"

#include <QList>

class V2XMessage;
class ConnectedAgent;
class ARandomGenerator;

class V2XFRAMEWORKEXPORT V2XBroker
{
public:

	V2XBroker();
	virtual ~V2XBroker();

	virtual void init() = 0;
	virtual void preUpdate(double time, double timeSta, double simStep) = 0;
	virtual void postUpdate(double time, double timeSta, double simStep) = 0;

	virtual void vehSubscription(ConnectedAgent * agent);
	virtual  void vehUnsubscription(ConnectedAgent * agent);
	virtual  void sendPoint2Point(double timeStamp, ConnectedAgent *to, V2XMessage *message);
	virtual  void broadcast(double timeStamp, V2XMessage *message);

	virtual V2XMessage *getNewMessage(int atype) = 0;

protected:
	QList <ConnectedAgent *> vehiclessubscribed;

};

