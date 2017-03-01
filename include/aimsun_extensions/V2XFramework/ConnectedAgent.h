//-*-Mode: C++;-*-
#ifndef _ConnectedAgent_h_
#define _ConnectedAgent_h_

#include "V2XFrameworkUtil.h"

#include "ADynamicAgent.h"


#include <QList>
#include <QMutex>

class VehicleRulesEngine;
class V2XBroker;
class V2XMessage;

class V2XFRAMEWORKEXPORT ConnectedAgent: public ADynamicAgent
{
public:
	ConnectedAgent(unsigned short idhandler, void *agent, VehicleRulesEngine * const avehRules, V2XBroker * const abroker);
	virtual ~ConnectedAgent();


	virtual void getState(double time, double timeSta) = 0;
	virtual void setState(double time, double timeSta) = 0;

	virtual void receiveMessage(V2XMessage *mess);

	virtual V2XBroker * getBroker() const;
	virtual VehicleRulesEngine * getVehicleRulesEngine() const;
	virtual const QList<V2XMessage *> &getReceivedMessages() const;

protected:
	VehicleRulesEngine *rulesEngine;
	V2XBroker * v2xbrokerItem;

	QList<V2XMessage *> bufferMessages;
	QMutex mutex;

};

#endif

