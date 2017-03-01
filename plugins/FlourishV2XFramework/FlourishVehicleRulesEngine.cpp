#include "FlourishVehicleRulesEngine.h"
#include "FlourishConnectedAgent.h"

FlourishVehicleRulesEngine::FlourishVehicleRulesEngine(): VehicleRulesEngine()
{

}


FlourishVehicleRulesEngine::~FlourishVehicleRulesEngine()
{

}


bool FlourishVehicleRulesEngine::evaluate(ConnectedAgent * agent)
{
	bool res = true;
//	qDebug("FlourishVehicleRulesEngine::evaluate");
//	qDebug(" veh id = %d", agent->getId());
//	qDebug(" Number messages received = %d", agent->getReceivedMessages().size());
//	qDebug(" Message content");
//	foreach(V2XMessage *mess, agent->getReceivedMessages()){
//		mess->print();
//	}
//	qDebug(" End Message content");

	return res;
}
