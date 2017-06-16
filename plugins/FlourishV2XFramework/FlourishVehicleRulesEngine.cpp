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

	qDebug() << "Received CAMMessage from" << message->getSource();

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



	qDebug() << agent->getId() << "Received DENMMessage from" << message->getSource();
}

void FlourishVehicleRulesEngine::evaluate( const QSharedPointer<const SPATEMMessage> &message,
										   V2XSimpleAP *agent)
{
	Q_UNUSED(message);
	V2XConnectedAgent *connectedAgent = dynamic_cast<V2XConnectedAgent*> (agent);
	Q_ASSERT(connectedAgent != nullptr);


	qDebug() << agent->getId() << "Received SPATEMMessage from" << message->getSource();
}

void FlourishVehicleRulesEngine::evaluate( const QSharedPointer<const MAPEMMessage> &message, V2XSimpleAP *agent)
{
	V2XConnectedAgent *connectedAgent = dynamic_cast<V2XConnectedAgent*> (agent);
	Q_ASSERT(connectedAgent != nullptr);

	qDebug() << agent->getId() << "Received MAPEMMessage from" << message->getSource();

	const MAPEM_t* msg = message->constData();
	qDebug() << agent->getId() << "contains " << msg->map.intersections->list.count << "intersections";

	for (int i = 0; i < msg->map.intersections->list.count; ++i) {
		IntersectionGeometry_t *geom = msg->map.intersections->list.array[i];
		qDebug() << "Id: " << geom->id.id << " composed by: ";
		for (int j = 0; j < geom->laneSet.list.count; ++j) {
			GenericLane_t *lane = geom->laneSet.list.array[j];
			qDebug() << "Lane ID:" << lane->laneID;

			Q_ASSERT(lane->nodeList.present == NodeListXY_PR_nodes);

			qDebug() << "Shape of the section:";
			for (int k = 0; k < lane->nodeList.choice.nodes.list.count; ++k) {
				NodeXY *node = lane->nodeList.choice.nodes.list.array[k];
				qDebug() << "[" << node->delta.choice.node_LatLon.lat << ","
						 << node->delta.choice.node_LatLon.lon << "]";
			}

			if (lane->connectsTo != nullptr) {
				qDebug() << "Connects to:";
				for (int k = 0; k < lane->connectsTo->list.count; ++k) {
					Connection_t *connection = lane->connectsTo->list.array[k];
					qDebug() << "    LaneID:" << connection->connectingLane.lane;
					if (connection->signalGroup != nullptr)
						qDebug() << "    SignalGroupId:" << *connection->signalGroup;
				}
			}
		}
	}
}
