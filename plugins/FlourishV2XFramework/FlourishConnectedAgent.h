//-*-Mode: C++;-*-
#pragma once

#include "ConnectedAgent.h"
#include "FlourishCAMMessage.h"

class VehicleRulesEngine;
class V2XComms;

class FlourishConnectedAgent: public ConnectedAgent
{
public:

	FlourishConnectedAgent(unsigned short idhandler, void *agent, VehicleRulesEngine * const avehRules, V2XBroker * const abroker );
	virtual ~FlourishConnectedAgent();

	virtual void getState(double time, double timeSta);
	virtual void setState(double time, double timeSta);

private:
	void buildCAMMessage(double time, double timeSta, FlourishCAMMessage & mess);


};


