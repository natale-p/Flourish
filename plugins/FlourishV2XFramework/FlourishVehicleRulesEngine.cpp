/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#include "FlourishVehicleRulesEngine.h"
#include "FlourishConnectedAgent.h"

FlourishVehicleRulesEngine::FlourishVehicleRulesEngine(): V2XRulesEngine()
{

}


FlourishVehicleRulesEngine::~FlourishVehicleRulesEngine()
{

}


void FlourishVehicleRulesEngine::evaluate( const QSharedPointer<const CAMMessage> &message,
										   V2XSimpleAP *agent)
{
	Q_UNUSED(message);

	V2XConnectedAgent *connectedAgent = dynamic_cast<V2XConnectedAgent*> (agent);
	Q_ASSERT(connectedAgent != nullptr);

	qDebug() << "Received CAMMessage";

	//	qDebug("FlourishVehicleRulesEngine::evaluate");
	//	qDebug(" veh id = %d", agent->getId());
	//	qDebug(" Number messages received = %d", agent->getReceivedMessages().size());
	//	qDebug(" Message content");
	//	foreach(V2XMessage *mess, agent->getReceivedMessages()){
	//		mess->print();
	//	}
	//	qDebug(" End Message content");
}

void FlourishVehicleRulesEngine::evaluate( const QSharedPointer<const DENMMessage> &message,
										   V2XSimpleAP *agent)
{
	Q_UNUSED(message);
	V2XConnectedAgent *connectedAgent = dynamic_cast<V2XConnectedAgent*> (agent);
	Q_ASSERT(connectedAgent != nullptr);



	qDebug() << "Received DENMMessage";
}

void FlourishVehicleRulesEngine::evaluate( const QSharedPointer<const SPATEMMessage> &message,
										   V2XSimpleAP *agent)
{
	Q_UNUSED(message);
	V2XConnectedAgent *connectedAgent = dynamic_cast<V2XConnectedAgent*> (agent);
	Q_ASSERT(connectedAgent != nullptr);


	qDebug() << "Received SPATEMMessage";
}

void FlourishVehicleRulesEngine::evaluate( const QSharedPointer<const MAPEMMessage> &message, V2XSimpleAP *agent)
{
	Q_UNUSED(message);
	V2XConnectedAgent *connectedAgent = dynamic_cast<V2XConnectedAgent*> (agent);
	Q_ASSERT(connectedAgent != nullptr);


	qDebug() << "Received MAPEMMessage";
}
