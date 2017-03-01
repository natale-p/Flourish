#pragma once

#include "V2XFrameworkUtil.h"
#include "V2XBroker.h"


#include <QMultiMap>


class ARandomGenerator;

class V2XFRAMEWORKEXPORT V2XRandomBroker: public V2XBroker
{
public:
	V2XRandomBroker();
	virtual ~V2XRandomBroker();

	virtual void setRandomSeed(unsigned avalue);
	virtual void setParam(double alatencyTimeMean, double alatencyTimeDev, double alatencyTimeMin, double alatencyTimeMax, double probabilityLost);


	virtual void init();
	virtual void preUpdate(double time, double timeSta, double simStep);
	virtual void postUpdate(double time, double timeSta, double simStep);

	virtual  void sendPoint2Point(double timeStamp, ConnectedAgent *to, V2XMessage *message);
	virtual  void broadcast(double timeStamp, V2XMessage *message);

	virtual V2XMessage *getNewMessage(int atype) = 0;

protected:

	class PendingMessage{
	public:
		PendingMessage(V2XMessage *amess, ConnectedAgent *ato):mess(amess), to(ato){}
		V2XMessage *mess;
		ConnectedAgent *to;

	};

	ARandomGenerator *randomGenerator;

	double latencyTimeMean;
	double latencyTimeStdDev;
	double latencyTimeMin;
	double latencyTimeMax;
	double probabilityPacketLost;

	double currentTime;
	double timeStep;

	QMultiMap < double, PendingMessage> pendingMessages;

	virtual bool isLostPacket(double aprob) const;
	virtual double getLatencyTime(double amean, double stdev, double min, double max) const;


};

